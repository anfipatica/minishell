#include "minishell.h"

void	join_tokens(t_token *node1, t_token *node2)
{
	char	*str_nodes;
	t_token *aux;

	if (node2->expanded)
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

	head = *list;
	while (*list)
	{
		if (((*list)->type == T_D_QUOTE || (*list)->type == T_S_QUOTE) ||
		 ((*list)->next && ((*list)->next->type == T_D_QUOTE || 
		 (*list)->next->type == T_S_QUOTE)))
		{
			//printf("type = %d, char = %c\n", (*list)->type, (*list)->next->str[0]);
			if ((*list)->next != NULL && !ft_strchr("|<> ", (*list)->next->str[0]))
			{
				join_tokens(*list, (*list)->next);
			}
			else
				*list = (*list)->next;
		}
		else
			*list = (*list)->next;
	}
	*list = head;
}