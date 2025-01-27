#include "minishell.h"


int	dup2_openeitor(char *file, int flags, mode_t mode, int system_fd)
{
	int	file_fd;

	file_fd = open(file, flags, mode);
	if (file_fd == -1)
	{
		perror(file);
		return OPEN_ERROR;
	}
	if (dup2(file_fd, system_fd) == -1)
		return (perror(file), OPEN_ERROR);
	close(file_fd);
	return (file_fd);
}

int	handle_files(t_redirect *file)
{
	int	state;

	state = 0;
	while (file && state != OPEN_ERROR)
	{
		if (file->redirect_type == T_REDIRECT_RIGHT)
			state = dup2_openeitor(file->name, O_REDIRECT_RIGHT, STD_PERMISSIONS, OUT_FILE);
		else if (file->redirect_type == T_APPEND)
			state = dup2_openeitor(file->name, O_REDIRECT_APPEND, STD_PERMISSIONS, OUT_FILE);
		else if (file->redirect_type == T_HERE_DOC)
			state = dup2_openeitor(file->name, O_HERE_DOC, 0, IN_FILE);
		else if (file->redirect_type == T_REDIRECT_LEFT)
			state = dup2_openeitor(file->name, O_REDIRECT_LEFT, 0, IN_FILE);
		if (file->redirect_type == T_HERE_DOC)
			unlink(file->name);
		file = file->next;
	}
	return (state);
}
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
		if (matrix[ARGS] == NULL)
			return ;
		path_name = find_path_name(matrix[ARGS][0], matrix[ENV], matrix[ARGS]);
		if (command->head_redirect)
			if (handle_files(command->head_redirect) == OPEN_ERROR)
			{
				exit(1);
			}
		execute_or_error(matrix, path_name);
		free_exit_execution(path_name, matrix);
	}
	else
	{
		wait(&status);
		dprintf(2, "STATUS: %d\n", WEXITSTATUS(status));
	}
}


int	executor_viejo(t_command *command)
{
	// int	heredoc_fd;

	// heredoc_fd = 0

	if (!command)
		return (0);
	// if (heredoc_fd == OPEN_ERROR)
	// 	return (false);
	exe_without_pipe(command);
	return (0);
}
// infile  es de 0 osea el de lectura
// outfile es de 1 osea el de escritura

void	child_pepa_new(t_command *command, int	action, int	p_fds[2])
{
	pid_t	pid_family;
	char 	**matrix[2];
	char	*path_name;


	pid_family = fork();
	if (pid_family == 0)
	{
		matrix[ARGS] = lts_args_to_matrix(command->args);
		matrix[ENV] = lts_env_to_matrix(command->env);
		dprintf(2, "asasd\n");
		if (matrix[ARGS] == NULL)
			return ;
		path_name = find_path_name(matrix[ARGS][0], matrix[ENV], matrix[ARGS]);
	
		dup2(p_fds[action], action);
		close(p_fds[action]);
		execute_or_error(matrix, path_name);
		free_exit_execution(path_name, matrix);
	}

}

int	executor(t_command *command)
{
	int		p_fds[2];
	int		status;

	pipe(p_fds);
	child_pepa_new(command, OUT_FILE, p_fds);
	close(p_fds[OUT_FILE]);
	child_pepa_new(command->next, IN_FILE, p_fds);
	close(p_fds[IN_FILE]);
	wait(&status);
	wait(&status);
	return (0);
}

void	continue_execution(t_command *command)
{
	print_commands(command);
	find_heredoc(command);
	if (!(command->next))
		exe_without_pipe(command); //- Perfecto
	else
		executor(command);
}
