#include "minishell.h"


/*
O_NOATIME -> no update de fecha en la lectura
O_TMPFILE -> crea un tempfile
O_TRUNC
*/
// void in_vs_out_file(int in_fd, int out_fd)
// {
// 	dprintf(2, "in_fd-> %d\n", in_fd);
// 	dprintf(2, "out_fd-> %d\n", out_fd);
// 	if (in_fd != NULL_FD)
// 	{
// 		dup2(in_fd, 0);
// 		close(in_fd);
// 	}
// 	if (out_fd != NULL_FD)
// 	{
// 		dup2(out_fd, 1);
// 		close(out_fd);
// 	}
// }

void dup2_file(int fd, int system_fd)
{
	if (fd == NULL_FD)
		return ;
	dup2(fd, system_fd);
	close(fd);
}

/*
in_fd puede ser:
 (-2) - NULL_FD    -> no hay redirección de infile.
 (-1) - OPEN_ERROR -> open ha fallado.
 (3 o >3)          -> fd existente, open ha funcionado.
*/
int	in_file(t_redirect *file)
{
	int	in_fd;

	in_fd =	NULL_FD;
	while (file)
	{
		if (file->redirect_type == T_REDIRECT_LEFT)
			in_fd = open(file->name, O_RDONLY);
		if (file->redirect_type == T_HERE_DOC)
			in_fd = open("/tmp/.caca", O_HERE_DOC, STD_PERMISSIONS);
		if (in_fd == OPEN_ERROR)
			return (ft_perror(file->name), in_fd);
		if (file->next == NULL)
			break ;
		file = file->next;
	}
	return (in_fd);
}

int	out_file(t_redirect *file)
{
	int	out_fd;

	out_fd = NULL_FD;
	while (file && out_fd != OPEN_ERROR)
	{
		if (file->redirect_type == T_REDIRECT_RIGHT)
			out_fd = open(file->name, O_REDIRECT_RIGHT, STD_PERMISSIONS);
		else if (file->redirect_type == T_APPEND)
			out_fd = open(file->name, O_REDIRECT_APPEND, STD_PERMISSIONS);
		if (out_fd == OPEN_ERROR)
			ft_perror(file->name);
		if (file->next == NULL)
			break ;
		file = file->next;
	}
	return (out_fd);
}

bool	handle_files(t_redirect *file)
{
	int	in_fd;
	int	out_fd;

	out_fd = out_file(file);
	if (out_fd == OPEN_ERROR)
		return (false);
	in_fd = in_file(file);
	if (in_fd == OPEN_ERROR)
		return (false);
	dup2_file(in_fd, 0);
	dup2_file(out_fd, 1);
	return (true);
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
			if (handle_files(command->head_redirect) == false)
			{
				exit(1);
			}
		printf("bluuuuuuuu dipintod id blu\n");
		execute_or_error(matrix, path_name);
		free_exit_execution(path_name, matrix);
	}
	else
	{
		wait(&status);
		dprintf(2, "STATUS: %d\n", WEXITSTATUS(status));
	}
}

int	executor(t_command *command)
{
	if (!command)
		return (0);
	exe_without_pipe(command);
	return (0);
}
