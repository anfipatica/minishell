
#include "minishell.h"

int	check_builtins(t_command *command)
{
	const char *builtins[] = {
		"cd",
		"echo",
		"env",
		"exit",
		"export",
		"pwd",
		"unset",
		NULL
	};
	int i;

	i = 0;	
	if (!command->args)
		return (false);
	while (builtins[i]  != NULL)
	{
		if (ft_strcmp(command->args->name, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}


int	exec_builtin(t_command *command)
{
	if (!command->args)
		return (1);
	if (ft_strcmp(command->args->name, "cd") == 0)
		return(ft_cd(command), 0);
	if (ft_strcmp(command->args->name, "echo") == 0)
		return(ft_echo(command), 0);
	if (ft_strcmp(command->args->name, "env") == 0)
		return(ft_env(command), 0);
	if (ft_strcmp(command->args->name, "exit") == 0)
		return(ft_exit(command), 0);
	if (ft_strcmp(command->args->name, "export") == 0)
		return(ft_export(command));
	if (ft_strcmp(command->args->name, "pwd") == 0)
		return(ft_pwd(), 0);
	if (ft_strcmp(command->args->name, "unset") == 0)
		return(ft_unset(command), 0);
	return (1);
}
