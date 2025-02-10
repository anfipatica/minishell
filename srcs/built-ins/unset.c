#include "minishell.h"

void ft_unset(t_command *command)
{
	(void)command;
	printf("FT_UNSET\n");

	// quero borrar el primer env;

	t_env **head_env = &(command->env->next);
	ft_free_one_env(command->env);
	command->env = *head_env;




	/* t_env **old_node;

	old_node = &command->env;

	head_env = command->env;
	// if (ft_strcmp(head_env->name, command->args) == 0)
	if (1)
	{
		(*old_node)->next = head_env->next;
		ft_free_one_env(head_env);
	}
	command->env = (*old_node); */
}


/* 
 -HEAD
 - ↓
   a -> b -> c

a -> c

*/