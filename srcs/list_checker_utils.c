/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_checker_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:17:33 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/27 19:18:45 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_tokens(t_token *node1, t_token *node2)
{
	char	*str_nodes;
	t_token	*aux;

	str_nodes = ft_strjoin(
			ft_ternary(node1->expanded, node1->expanded, node1->str),
			ft_ternary(node2->expanded, node2->expanded, node2->str));
	if (node1->free_expanded == true)
		free(node1->expanded);
	node1->expanded = str_nodes;
	str_nodes = ft_strjoin(node1->str, node2->str);
	free(node1->str);
	node1->str = str_nodes;
	aux = node2->next;
	ft_free_one_node(node2);
	node1->free_expanded = true;
	node1->next = aux;
}

void	unlink_node(t_token **before_space)
{
	t_token	*space;

	space = (*before_space)->next;
	(*before_space)->next = (*before_space)->next->next;
	ft_free_one_node(space);
	(*before_space) = (*before_space)->next;
}

void	turn_to_word(t_token *token)
{
	if (token->type == T_S_QUOTE || token->type == T_D_QUOTE)
		token->type = T_WORD;
}
