#include "minishell.h"

//si el comando coincide con el name de env entonces delete one node
void ft_unset(t_command *command)
{
	t_args *next_args;
	t_env	*aux_to_del;

	next_args = command->args->next;
	while(command->env->next)
	{
		if (ft_strcmp(next_args->name, command->env->next->name) == 0)
		{
			aux_to_del = command->env->next;
			command->env->next = command->env->next->next;
			ft_free_one_env(aux_to_del);
			break ;
		}
		command->env = command->env->next;
	}
}

/* 
 -HEAD
 - ↓
   a -> b -> c

a -> c

*/

