#include "minishell.h"

void	exe_without_pipe(char * first_cmd, char **envp)
{
	pid_t	family;
	int		in_fd;
	char	**cmd_arg;
	char	*path_name;

	family = fork();
	if (family == 0)
	{
		if (cmd_arg == NULL)
			exit(1);
		path_name = find_path_name(cmd_arg[0], envp, cmd_arg);
		if (path_name != NULL)
			execve(path_name, cmd_arg, envp);
		free(path_name);
		ft_perror(cmd_arg[0]);
		free_double_pointer(cmd_arg);
		exit(1);
	}
}

int	executor(t_command *command)
{
	command->path_command = find_path_name(command->args->arg, command->env, NULL);
	return (printf("command->path_command: %s\n", command->path_command));
	exe_without_pipe(command->path_command, command->env)
}
