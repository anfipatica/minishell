#include "minishell.h"

#define O_REDIRECT_RIGHT (O_WRONLY | O_CREAT | O_TRUNC)
#define O_REDIRECT_APPEND (O_WRONLY | O_CREAT | O_APPEND)

#define STD_PERMISSIONS 0644

/*
O_NOATIME -> no update de fecha en la lectura
O_TMPFILE -> crea un tempfile
O_TRUNC
*/

void	handle_files(t_redirect *file)
{
	int	fd_file;

	while (file)
	{
		if (file->redirect_type == T_REDIRECT_RIGHT)
			fd_file = open(file->name, O_REDIRECT_RIGHT, STD_PERMISSIONS);
		else if (file->redirect_type == T_APPEND)
			fd_file = open(file->name, O_REDIRECT_APPEND, STD_PERMISSIONS);
		file = file->next;
	}
	dup2(fd_file, 1);
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
		handle_files(command->aux_redirect);
		execute_or_error(matrix, path_name);
		free_exit_execution(path_name, matrix);
	}
	else
	{
		wait(&status);
	//	printf("STATUS: %d\n", WTERMSIG(status));
	}
}

int	executor(t_command *command)
{
	if (!command)
		return (0);
	exe_without_pipe(command);
	return (0);
}
