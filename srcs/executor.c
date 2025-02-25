#include "minishell.h"

void	execute_or_error(char **matrix[2], char *path_name)
{
	struct stat	buffer;

	if (!path_name || !path_name[0])
		return (error_exit(matrix[ARGS][0], COMMAND_NOT_FOUND));
	execve(path_name, matrix[ARGS], matrix[ENV]);
	if (stat(path_name, &buffer) == -1)
		ft_perror(matrix[ARGS][0]);
	else if ((buffer.st_mode & __S_IFMT) == __S_IFDIR)
		error_exit(path_name, IS_DIR);
	else //? Por ahora funciona pero quizás haya más casos???
		error_exit(path_name, NO_PERMISSION);
//	printf("*********%d\n", (buffer.st_mode & S_IXUSR));
	//else if ((buffer.st_mode & S_IXUSR))
}


void	restore_fds(int aux_stdout, int aux_stdin)
{
	dup2(aux_stdout, 1);
	close(aux_stdout);
	dup2(aux_stdin, 0);
	close(aux_stdin);
}

	/*
		  ~ ps -e | grep mini
		 519234 pts/1    00:00:00 minishell
		➜  ~ lsof -p 519234  
	*/
bool	builtin_without_pipe(t_command *command)
{
	int aux_stdout;
	int aux_stdin;
	if (command->next)
		return (false);
	if (check_builtins(command) == false)
		return (false);
	aux_stdout = dup(OUT_FILE);
	aux_stdin = dup(IN_FILE);
	if (handle_files(command->head_redirect) == OPEN_ERROR)
	{
		g_exit_status = EXIT_STATUS_ERROR;
		restore_fds(aux_stdout, aux_stdin);
		return (true);
	}
	if (exec_builtin(command) == true)
	{
		restore_fds(aux_stdout, aux_stdin);
		return (true);
	}
	return (false);
}

void wait_all(void)
{
	int	current_status;
	int	last_process_status;
	pid_t	current_wp;
	pid_t	last_wp;

	current_wp = 0;
	last_wp = 0;
	while (current_wp != -1)
	{
		//!Por qué "sleep 2 | ./a" sale como que current_status es 0.
		current_wp = waitpid(-1, &current_status, 0);
		printf("\ncurrent_wp: %d, last_wp: %d, current_status: %d\n", current_wp, last_wp, current_status);
		if (current_wp > last_wp)
		{
			last_process_status = current_status;
			last_wp = current_wp;
			printf("last_wp: %d, last_process_status: %d\n", last_wp, last_process_status);
		}
		if (WIFEXITED(last_process_status)) //-Si ha salido bien.
			g_exit_status = WEXITSTATUS(last_process_status);
		else if (WIFSIGNALED(last_process_status)) //-Si ha salido con una señal.
			g_exit_status = WTERMSIG(last_process_status) + 128;
	}
}

void exec_jr(t_command *command, int in_fd, int *pipefd)
{
	char 	**matrix[2];
	char 	*path_name;
	pid_t 	family;

	family = fork();
	if (family == CHILD)
	{
		if (in_fd != NULL_FD)
		{
			dup2(in_fd, 0);
			close(in_fd);
		}
		if (command->next)
		{
			close(pipefd[IN_FILE]);
			dup2(pipefd[OUT_FILE], 1);
			close(pipefd[OUT_FILE]);
		}
		if (handle_files(command->head_redirect) == OPEN_ERROR)
			exit(1);
		if (exec_builtin(command) == true)
		{
			exit(g_exit_status);
		}
		matrix[ARGS] = lts_args_to_matrix(command->args);
		matrix[ENV] = lts_env_to_matrix(command->env);
		if (matrix[ARGS] == NULL)
			exit(0);
		path_name = find_path_name(matrix[ARGS][0], matrix[ENV], matrix[ARGS]);
		execute_or_error(matrix, path_name);
		perror(path_name);
		printf("errno: %d\n", errno);
		exit(g_exit_status); //!Gestionar mejor esto
	}
	signal(SIGINT, child_signal_handler);
	//!GESTIONAR EL SIGQUIT CUANDO ES INTERACTIVO!!!!!!!!!!!!!!!!!!!!!!!!!!11111
}

int	daddy_executor(t_command *command)
{
	int		pipefd[2] = {0, 1};
	int		in_fd = NULL_FD;
	int 	mutiple_commands;
	
	mutiple_commands = true;
	if (command->next == NULL)
		mutiple_commands = false;
	while (command)
	{
		if (command->next)
			pipe(pipefd);
		exec_jr(command, in_fd, pipefd);
		if (mutiple_commands == true)
		{
			close(in_fd);
			in_fd = pipefd[IN_FILE];
			close(pipefd[OUT_FILE]);
		}
		command = command->next;
	}
	if (mutiple_commands == true)
		close(pipefd[IN_FILE]);
	wait_all();
	return (0);
}

////Si no se comprueba command->args, da segfault. Si nos pasan "> file", es válido y falla.
////Ya no da segfault pero no debería ejecutar nada y ahora salta como si no hubiera encontrado el comando "".
void	begin_execution(t_command *command)
{
	if (find_heredoc(command) == SIGINT_SIGNAL)
		return ;

	if (g_exit_status == SIGINT_SIGNAL || builtin_without_pipe(command) == true)
		return ;
	daddy_executor(command);
}

 //- REVISAR LO DE SI NO HAY NINGÚN COMANDO Y SOLO REDIRECCIONES.
/*
! OJO si tenemos un solo comando y es bulidig tiene que executarse en el padre;
! si es mas de un comanddo entonces todo pasa en los hijos;
! porquee no tendrias quee cerra nuestra minichell!!!!!
*/