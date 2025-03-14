/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:19:00 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/27 19:26:36 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_command *command)
{
	if (command->args->next)
	{
		g_exit_status = COMMAND_NOT_FOUND;
		return ;
	}
	while (command->env)
	{
		if (command->env->value)
			printf("%s=%s\n", command->env->name, command->env->value);
		command->env = command->env->next;
	}
}
