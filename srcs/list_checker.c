#include "minishell.h"

void	list_checker(t_token **list)
{
	t_token *head;
	char	*str_nodes;
	t_token *aux;

	head = *list;
	while (*list)
	{
		if (((*list)->type == T_D_QUOTE) && ((*list)->type == T_S_QUOTE))
		{
			if ((*list)->next != NULL && (*list)->next->str[0] > ' ')
			{
				if ((*list)->next->expanded)
					str_nodes = ft_strjoin((*list)->expanded, (*list)->next->expanded);
				else
					str_nodes = ft_strjoin((*list)->expanded, (*list)->next->str);
				aux = (*list)->next->next;
				ft_free_one_node((*list)->next);
				(*list)->next = aux;
				print_tokens(*list);
			}
		}
		*list = (*list)->next;
	}
	print_tokens(head);
	*list = head;
}