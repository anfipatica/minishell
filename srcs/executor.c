#include "minishell.h"

void	dir_or_file(char **matrix[2], char *path_name)
{
	struct stat	buffer;

	if (!path_name)
		return (error_exit(matrix[ARGS][0], COMMAND_DOESNT_EXIST));
	execve(path_name, matrix[ARGS], matrix[ENV]);
	if (stat(path_name, &buffer) == -1)
		ft_perror(matrix[ARGS][0]);
	else if ((buffer.st_mode & __S_IFMT) == __S_IFDIR)
		return (error_exit(path_name, IS_DIR));
}

void	exe_without_pipe(t_command *command)
{
	pid_t	family;
	int	status;
	char	*path_name;
	char **matrix[2];

	family = fork();
	if (family == 0)
	{
		matrix[ARGS] = lts_args_to_matrix(command->args);
		matrix[ENV] = lts_env_to_matrix(command->env);
		if (matrix[ARGS] == NULL)
			return ;
		path_name = find_path_name(matrix[ARGS][0], matrix[ENV], matrix[ARGS]);
		printf("path_name = %s\n", path_name);
		dir_or_file(matrix, path_name);
		free(path_name);
		free(matrix[ARGS]);
		free_double_pointer(matrix[ENV]);
		exit(1);
	}
	else
		wait(&status);
}

int	executor(t_command *command)
{
	if (!command)
		return (0);
//	command->path_command = find_path_name(command->args->arg, command->env, NULL);

	/*...*/
	exe_without_pipe(command);

	//-al final:

	return (0);
}

// void	exe_without_pipe(char **cmd_arg, char **envp)
// {
// 	pid_t	family;
// 	int	status;
// 	char	*path_name;

// 	family = fork();
// 	if (family == 0)
// 	{
// 		if (cmd_arg == NULL)
// 			return ;
// 		path_name = find_path_name(cmd_arg[0], envp, cmd_arg);
// 		printf("path_name: %s\n", path_name);
// 		if (path_name)
// 			execve(path_name, cmd_arg, envp);
// 		free(path_name);
// 		ft_perror(cmd_arg[0]);
// 	}
// 	else
// 		wait(&status);
// }

// #define	ARGS	0
// #define	ENV	1

// int	executor(t_command *command)
// {
// 	char **matrix[2];

// 	if (!command)
// 		return (0);
// //	command->path_command = find_path_name(command->args->arg, command->env, NULL);
// 	matrix[ARGS] = lts_args_to_matrix(command->args);
// 	matrix[ENV] = lts_env_to_matrix(command->env);
// 	/*...*/
// 	exe_without_pipe(matrix[ARGS], matrix[ENV]);

// 	//-al final:
// 	free(matrix[ARGS]);
// 	free_double_pointer(matrix[ENV]);
// 	return (printf("command->path_command: %s\n", command->path_command));
// }
