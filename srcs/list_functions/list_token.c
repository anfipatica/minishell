/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:08:05 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/03/05 16:32:38 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * new_token creates a new token and allocates memory for it.
 */
t_token	*new_token(t_token_value type, char *str, int length)
{
	t_token	*new_token;

	new_token = (t_token *) ft_calloc(sizeof(t_token), 1);
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->str = ft_substr(str, 0, length);
	new_token->length = length;
	if (type == T_S_QUOTE)
	{
		new_token->expanded = ft_substr(str, 1, length - 2);
		new_token->free_expanded = true;
	}
	else
	{
		new_token->expanded = NULL;
		new_token->free_expanded = false;
	}
	new_token->next = NULL;
	return (new_token);
}

/**
 * add_token_back receives the head of the list and the new token
 * to add at the end of said list. If there is no head, new becomes it.
 */
void	add_token_back(t_token **lst, t_token *new)
{
	t_token	*temp;

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

void	ft_free_one_node(t_token *token)
{
	if (!token)
		return ;
	free(token->str);
	token->str = NULL;
	if (token->expanded && token->free_expanded == true)
	{
		free(token->expanded);
		token->expanded = NULL;
		token->free_expanded = false;
	}
	free(token);
	token = NULL;
}

/**
 * ft_free_tokens frees the nodes of a list and the neccesary content
 * inside each of them.
 */
void	ft_free_tokens(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;
	while (token != NULL)
	{
		temp = token->next;
		ft_free_one_node(token);
		token = temp;
	}
	token = NULL;
}
