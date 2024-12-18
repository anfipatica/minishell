
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
	t_token *aux;

	node1->free_expanded = true;
	str_nodes = ft_strjoin(get_valid_string(node1), get_valid_string(node2));
	free(node1->expanded);
	node1->expanded = str_nodes;
	str_nodes = ft_strjoin(node1->str, node2->str);
	free(node1->str);
	node1->str = str_nodes;
	aux = node2->next;
	ft_free_one_node(node2);
	node1->next = aux;
}

void	unlink_node(t_token **before_space)
{
	t_token *space;

	space = (*before_space)->next;
	(*before_space)->next = (*before_space)->next->next;
	ft_free_one_node(space);
	(*before_space) = (*before_space)->next;
}

void	list_checker(t_token **list)
{
	t_token *aux_list;

	if ((*list)->type == T_SPACE)
	{
		aux_list = (*list)->next;
		ft_free_one_node(*list);
		*list = aux_list;
	}
	else
		aux_list = *list;
	while (aux_list && aux_list->next)
	{
		if (aux_list->type == T_S_QUOTE || aux_list->type == T_D_QUOTE)
			aux_list->type = T_WORD;
		if (aux_list->next && (aux_list->next->type == T_S_QUOTE || aux_list->next->type == T_D_QUOTE))
			aux_list->next->type = T_WORD;
		if (aux_list->type == T_WORD && aux_list->next->type == T_WORD)
			join_tokens(aux_list, aux_list->next);
		else if (aux_list->type == T_WORD && aux_list->next->type == T_ENV)
		{
			join_tokens(aux_list, aux_list->next);
		}
		else if (aux_list->type == T_ENV && aux_list->next->type == T_WORD)
		{
			join_tokens(aux_list, aux_list->next);
		}
		else if (aux_list->type == T_ENV && aux_list->next->type == T_ENV)
		 	join_tokens(aux_list, aux_list->next);
		else if (aux_list->next->type == T_SPACE)
			unlink_node(&aux_list);
		else
			aux_list = aux_list->next;
	}
	if (aux_list && (aux_list->type == T_D_QUOTE || aux_list->type == T_S_QUOTE))
		aux_list->type = T_WORD;
}
