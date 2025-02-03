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

void	exe_without_pipe(t_command *command)
{
	pid_t	family;
	int		status;
	char	*path_name;
	char 	**matrix[2];

	family = fork();
	if (family == 0)
	{
		matrix[ARGS] = lts_args_to_matrix(command->args);
		matrix[ENV] = lts_env_to_matrix(command->env);
		if (handle_files(command->head_redirect) == OPEN_ERROR)
			exit(1);
		if (matrix[ARGS] == NULL)
			exit(0);
		path_name = find_path_name(matrix[ARGS][0], matrix[ENV], matrix[ARGS]);
		execute_or_error(matrix, path_name);
		free_exit_execution(path_name, matrix);
	}
	else
	{
		wait(&status);
		dprintf(2, "STATUS: %d\n", WEXITSTATUS(status));
	}
}

// cmd | cmd2

int	executor(t_command *command)
{
	int		pipefd[2];
	int		status;
	int		old_fd;

	while (command)
	{
		if(command->next)
			pipe(pipefd);
		funcion_que_executa(command, old_fd, pipefd);
		old_fd = pipefd[IN_FILE];
		close(pipefd[OUT_FILE]);
	}
	close(pipefd[IN_FILE]);
	// child_pepa_new(command, OUT_FILE, pipefd);
	// close(pipefd[OUT_FILE]);
	// child_pepa_new(command->next, IN_FILE, pipefd);
	// close(pipefd[IN_FILE]);

	// wait(&status);
	return (0);
}

void	begin_execution(t_command *command)
{
	print_commands(command);
	find_heredoc(command);
	//!Si no se comprueba command->args, da segfault. Si nos pasan "> file", es válido y falla.
	//!Ya no da segfault pero no debería ejecutar nada y ahora salta como si no hubiera encontrado el comando "".
	if (check_builtins(command) == 0)
		return ;
	if (!(command->next))
		exe_without_pipe(command); //- REVISAR LO DE SI NO HAY NINGÚN COMANDO Y SOLO REDIRECCIONES.
	else
		executor(command);
}
/*
! OJO si tenemos un solo comando y es bulidig tiene que executarse en el padre;
! si es mas de un comanddo entonces todo pasa en los hijos;
! porquee no tendrias quee cerra nuestra minichell!!!!!
*/