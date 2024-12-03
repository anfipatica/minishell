
#include "minishell.h"

void	join_tokens(t_token *node1, t_token *node2)
{
	char	*str_nodes;
	t_token *aux;

	if (node1->type != T_D_QUOTE && node1->type != T_S_QUOTE)
		node1->type = node2->type;
	node1->free_expanded = true;
	if (node1->expanded == NULL)
		str_nodes = ft_strjoin(node1->str, node2->expanded);
	else if (node2->expanded != NULL)
		str_nodes = ft_strjoin(node1->expanded, node2->expanded);
	else
		str_nodes = ft_strjoin(node1->expanded, node2->str);
	free(node1->expanded);
	node1->expanded = str_nodes;
	str_nodes = ft_strjoin(node1->str, node2->str);
	free(node1->str);
	node1->str = str_nodes;
	aux = node2->next;
	ft_free_one_node(node2);
	node1->next = aux;
}

void	list_checker(t_token **list)
{
	t_token *head;
	t_token *lst;

	lst = *list;
	head = *list;
	while (lst)
	{
		if ((lst->type == T_D_QUOTE || lst->type == T_S_QUOTE) ||
		 (lst->next && (lst->next->type == T_D_QUOTE || 
		 lst->next->type == T_S_QUOTE)))
		{
			if (lst->next != NULL && !ft_strchr("|<> ", lst->next->str[0]))
				join_tokens(*list, lst->next);
			else
				lst = lst->next;
		}
		else
			lst = lst->next;
	}
	lst = head;
}