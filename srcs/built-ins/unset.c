/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:32 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/27 19:35:00 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_command *command)
{
	t_args	*next_args;
	t_env	*aux_to_del;
	t_env	*head_env;

	head_env = command->env;
	next_args = command->args->next;
	while (next_args)
	{
		while (command->env->next)
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
		command->env = head_env;
		next_args = next_args->next;
	}
	g_exit_status = OK;
}
