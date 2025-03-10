/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:16:11 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/03/05 13:28:19 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_new_node_by_env(t_token *env_node)
{
	t_token	*head;
	t_token	*new;
	char	**env_splitted;
	int		i;

	head = NULL;
	new = NULL;
	env_splitted = ft_split(env_node->expanded, ' ');
	i = 0;
	while (env_splitted[i])
	{
		new = new_token(T_WORD, env_node->str, env_node->length);
		new->expanded = ft_strdup(env_splitted[i]);
		new->free_expanded = true;
		add_token_back(&head, new);
		if (env_splitted[i + 1])
			add_token_back(&head, new_token(T_SPACE, " ", 1));
		free(env_splitted[i]);
		i++;
	}
	free(env_splitted);
	new->next = env_node->next;
	ft_free_one_node(env_node);
	return (head);
}

void	list_checker(t_token **list)
{
	t_token	*curr_node;
	t_token	*next;

	*list = check_and_delete_env(*list, NULL);
	if (!(*list))
		return ;
	turn_to_word(*list);
	if ((*list)->type == T_ENV)
		*list = create_new_node_by_env(*list);
	curr_node = *list;
	while (curr_node->next)
	{
		next = curr_node->next;
		turn_to_word(next);
		if (next->type == T_ENV)
			curr_node->next = create_new_node_by_env(next);
		else if (curr_node->type == T_WORD && next->type == T_WORD)
			join_tokens(curr_node, next);
		else
			curr_node = next;
	}
	*list = check_and_delete_space(*list);
}
