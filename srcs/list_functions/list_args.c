/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:04:06 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/27 20:12:10 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	len_list_args(t_args *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char	**lts_args_to_matrix(t_args *args)
{
	char	**args_matrix;
	int		i;

	if (!args)
		return (NULL);
	args_matrix = malloc((len_list_args(args) + 1) * sizeof(char *));
	if (!args_matrix)
		return (NULL);
	i = 0;
	while (args)
	{
		args_matrix[i] = args->name;
		i++;
		args = args->next;
	}
	args_matrix[i] = NULL;
	return (args_matrix);
}

t_args	*new_args(char *arg)
{
	t_args	*new_args;

	new_args = (t_args *) malloc(sizeof(t_args));
	if (!new_args)
		return (NULL);
	new_args->name = arg;
	new_args->next = NULL;
	return (new_args);
}

/**
 * add_args_back receives the head of the list and the new args
 * to add at the end of said list. If there is no head, new becomes it.
 */
void	add_args_back(t_args **head, t_args *new)
{
	t_args	*temp;

	if (*head == NULL)
	{
		*head = new;
		new->next = NULL;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}
