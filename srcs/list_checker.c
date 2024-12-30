
#include "minishell.h"

// char *ft_ternary(void *true_case, void *false_case, bool condition)
// {
// 	if (condition)
// 		return (true_case);
// 	return (false_case);
// }

char *get_valid_string(t_token *node)
{
	if (node->expanded)
		return (node->expanded);
	return (node->str);
}


void	join_tokens(t_token *node1, t_token *node2)
{
	char	*str_nodes;

	node1->free_expanded = true;
	str_nodes = ft_strjoin(get_valid_string(node1), get_valid_string(node2));
	free(node1->expanded);
	node1->expanded = str_nodes;
	str_nodes = ft_strjoin(node1->str, node2->str);
	free(node1->str);
	node1->str = str_nodes;
	ft_free_one_token(node2);
}

/* void	unlink_node(t_token **before_space)
{
	t_token *space;

	space = (*before_space)->next;
	(*before_space)->next = (*before_space)->next->next;
	ft_free_one_node(space);
	(*before_space) = (*before_space)->next;
} */

bool	predicate_if_join(t_token *token1, t_token *token2)
{
	if (token2)
	{
		if (token1->type == T_WORD && token2->type == T_WORD)
			return (true);
		else if (token1->type == T_WORD && token2->type == T_ENV)
			return (true);
		else if (token1->type == T_ENV && token2->type == T_WORD)
			return (true);
		else if (token1->type == T_ENV && token2->type == T_ENV)
			return (true);
	}
	return (false);
}

void	list_checker(void *list)
{
	t_list *aux_list;
	t_token	*aux1;
	t_token	*aux2;

	aux_list = (t_list *)list;
	aux1 = (t_token *)(aux_list->content);
	aux2 = (t_token *)(aux_list->next->content);
	if (aux1->type == T_S_QUOTE || aux1->type == T_D_QUOTE)
		aux1->type = T_WORD;
	if (aux2 && (aux2->type == T_S_QUOTE || aux2->type == T_D_QUOTE))
		aux2->type = T_WORD;
	if (predicate_if_join(aux1, aux2) == true)
		join_tokens(aux1, aux2);
}


/* void	list_checker(t_list **list)
{
	t_token *aux_list;

	if (((t_token *)((*list)->content))->type == T_SPACE)
	{
		aux_list = (*list)->next;
		ft_lstdelone(*list, ft_free_one_node(*list));
		*list = aux_list;
	}
	else
		aux_list = *list;
	while (aux_list && aux_list->next)
	{



		else if (aux_list->next->type == T_SPACE)
			unlink_node(&aux_list);
		else
			aux_list = aux_list->next;
	}
	if (aux_list && (aux_list->type == T_D_QUOTE || aux_list->type == T_S_QUOTE))
		aux_list->type = T_WORD;
} */
