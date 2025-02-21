
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


bool	exec_builtin(t_command *command)
{
	if (!command->args)
		return (1);
	if (ft_strcmp(command->args->name, "cd") == false)
		return(ft_cd(command), true);
	if (ft_strcmp(command->args->name, "echo") == false)
		return(ft_echo(command), true);
	if (ft_strcmp(command->args->name, "env") == false)
		return(ft_env(command), true);
	if (ft_strcmp(command->args->name, "exit") == false)
		return(ft_exit(command), true);
	if (ft_strcmp(command->args->name, "export") == false)
		return(ft_export(command), true);
	if (ft_strcmp(command->args->name, "pwd") == false)
		return(ft_pwd(), true);
	if (ft_strcmp(command->args->name, "unset") == false)
		return(ft_unset(command), true);
	return (false);
}
