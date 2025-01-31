
#include "minishell.h"

int	check_builtins(t_command *command)
{
	if (ft_strcmp(command->args->name, "cd") == 0)
		return(ft_cd(), 0);
	if (ft_strcmp(command->args->name, "echo") == 0)
		return(ft_echo(), 0);
	if (ft_strcmp(command->args->name, "env") == 0)
		return(ft_env(command), 0);
	if (ft_strcmp(command->args->name, "exit") == 0)
		return(ft_exit(), 0);
	if (ft_strcmp(command->args->name, "export") == 0)
		return(ft_export(), 0);
	if (ft_strcmp(command->args->name, "pwd") == 0)
		return(ft_pwd(), 0);
	if (ft_strcmp(command->args->name, "unset") == 0)
		return(ft_unset(), 0);
	return (1);
}
