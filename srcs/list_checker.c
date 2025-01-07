
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

	printf("en join_tokens\n");
	node1->free_expanded = true;
	str_nodes = ft_strjoin(get_valid_string(node1), get_valid_string(node2));
	free(node1->expanded);
	node1->expanded = str_nodes;
	str_nodes = ft_strjoin(node1->str, node2->str);
	free(node1->str);
	node1->str = str_nodes;
	printf("node2 = %p\n", node2);
	ft_free_one_token(&node2);
	printf("node2 = %p\n", node2);
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

void	list_checker(void *node1, void *node2)
{
	t_token	*aux1;
	t_token	*aux2;

	aux1 = (t_token *)(node1);
	aux2 = (t_token *)(node2);
	if (aux1->type == T_S_QUOTE || aux1->type == T_D_QUOTE)
		aux1->type = T_WORD;
	if (aux2 && (aux2->type == T_S_QUOTE || aux2->type == T_D_QUOTE))
		aux2->type = T_WORD;
	if (predicate_if_join(aux1, aux2) == true)
		join_tokens(aux1, aux2);
}

