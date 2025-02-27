/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:06:17 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/27 20:25:15 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * new_token creates a new token and allocates memory for it.
 */
t_command	*new_command(t_env *env, t_token *token)
{
	t_command	*new_command;

	new_command = (t_command *) malloc(sizeof(t_command));
	if (!new_command)
		return (NULL);
	new_command->path_command = NULL;
	new_command->args = NULL;
	new_command->head_redirect = NULL;
	new_command->env = env;
	new_command->next = NULL;
	new_command->token_pointer = token;
	new_command->execve_matrix = NULL;
	return (new_command);
}

/**
 * add_command_back receives the head of the list and the new command
 * to add at the end of said list. If there is no head, new becomes it.
 */
void	add_command_back(t_command **lst, t_command *new)
{
	t_command	*temp;

	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_free_one_command(t_command *command)
{
	if (!command)
		return ;
	free(command->path_command);
	ft_free_redirects(command->head_redirect);
	ft_free_list_args(command->args);
	free(command);
}

void	ft_free_commands(t_command *command)
{
	t_command	*temp;

	if (!command)
		return ;
	while (command != NULL)
	{
		temp = command->next;
		ft_free_one_command(command);
		command = temp;
	}
}
