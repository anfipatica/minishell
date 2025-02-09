#include "minishell.h"

void ft_env(t_command *command)
{
	(void)command;
	printf("FT_ENV\n");
	while(command->env)
	{
		printf("%s=%s\n", command->env->name, command->env->value);
		command->env = command->env->next;
	}
}
