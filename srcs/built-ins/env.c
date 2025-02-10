#include "minishell.h"

void ft_env(t_command *command)
{
	t_env	*env;

	env = command->env;
	while(env)
	{
		printf(PURPLE"%s"STD"=%s\n", env->name, env->value);
		env = env->next;
	}
}
