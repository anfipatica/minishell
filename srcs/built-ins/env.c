#include "minishell.h"

void ft_env(t_command *command)
{
	// t_env	*env;

	// env = command->env;
	while(command->env)
	{
		printf(PURPLE"%s"STD"=%s\n", command->env->name, command->env->value);
		command->env = command->env->next;
	}
}
