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
}

bool	builtin_without_pipe(t_command *command)
{
	int aux_stdout;
	int aux_stdin;

	aux_stdout = dup(1);
	aux_stdin = dup(0);
	if (command->next)
		return (false);
	if (check_builtins(command) == false)
		return (false);
	if (handle_files(command->head_redirect) == OPEN_ERROR)
		return (true);
	//g_exit_status = exec_builtin(command);
//	if (g_exit_status == 0)
	if (exec_builtin(command) == true)
	{
		dup2(aux_stdout, 1);
		close(aux_stdout);
		dup2(aux_stdin, 0);
		close(aux_stdin);
		return (true);
	}
	return (false);
}

void wait_all(void)
{
	int status;
	pid_t value_wp;

	value_wp = 0;
	while (value_wp != -1)
	{
		value_wp = waitpid(-1, &status, 0);
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
			dprintf(2, "ES BILT\n");
			exit(111);
		}
		matrix[ARGS] = lts_args_to_matrix(command->args);
		matrix[ENV] = lts_env_to_matrix(command->env);
		if (matrix[ARGS] == NULL)
			exit(0);
		path_name = find_path_name(matrix[ARGS][0], matrix[ENV], matrix[ARGS]);
		execute_or_error(matrix, path_name);
		exit(1); //!Gestionar mejor esto
	}
	signal(SIGINT, child_signal_handler);
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
	static unsigned char last_status;

	find_heredoc(command);
	if (last_status == g_exit_status)
		last_status = 0;
	else
		last_status = g_exit_status;

	if (last_status == SIGINT_SIGNAL || builtin_without_pipe(command) == true)
		return ;
	printf("holaaaaaa\n");
	daddy_executor(command);
}

 //- REVISAR LO DE SI NO HAY NINGÚN COMANDO Y SOLO REDIRECCIONES.
/*
! OJO si tenemos un solo comando y es bulidig tiene que executarse en el padre;
! si es mas de un comanddo entonces todo pasa en los hijos;
! porquee no tendrias quee cerra nuestra minichell!!!!!
*/