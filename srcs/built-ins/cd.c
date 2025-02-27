/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:36:21 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/27 19:36:56 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_command *command)
{
	while (command->env)
	{
		if (ft_strcmp("PWD", command->env->name) == 0)
		{
			free(command->env->value);
			command->env->value = getcwd(NULL, 0);
		}
		command->env = command->env->next;
	}
}

void	ft_cd(t_command *command)
{
	int	status;

	if (command->args->next == NULL)
	{
		status = chdir(ft_getenv("HOME", command->env, 0));
		if (status == CHDIR_ERROR)
			write(2, "cd: HOME not set\n", 18);
	}
	else
	{
		status = chdir(command->args->next->name);
		if (status == CHDIR_ERROR)
			perror(command->args->next->name);
	}
	update_pwd(command);
	if (status == CHDIR_ERROR)
		g_exit_status = CD_ERROR;
	else
		g_exit_status = OK;
}
