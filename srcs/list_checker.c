
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

	//printf("node1 = %s, node2 = %s\n", node1->str, node2->str);
	node1->free_expanded = true;
	str_nodes = ft_strjoin(get_valid_string(node1), get_valid_string(node2));
	//printf("desde join_tokens node1->expanded es null: %s\n", str_nodes);
	
	printf("jointokens\n");
	printf("dir expanded: %p\n", node1->expanded);
	printf("value expanded: %s\n", node1->expanded);
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
	t_token *new_list;

	new_list = *list;
	printf("listchecker!!!\n");
	while (new_list && new_list->next)
	{
		if (new_list->type == T_S_QUOTE || new_list->type == T_D_QUOTE)
			new_list->type = T_WORD;
		if (new_list->next && (new_list->next->type == T_S_QUOTE || new_list->next->type == T_D_QUOTE))
			new_list->next->type = T_WORD;
		if (new_list->type == T_WORD && new_list->next->type == T_WORD)
			join_tokens(new_list, new_list->next);
		else if (new_list->type == T_WORD && new_list->next->type == T_ENV)
		{
			join_tokens(new_list, new_list->next);
		}
		else if (new_list->type == T_ENV && new_list->next->type == T_WORD)
		{

			join_tokens(new_list, new_list->next);
			printf("listchecker22222!!!\n");
		}
		else if (new_list->type == T_ENV && new_list->next->type == T_ENV)
			join_tokens(new_list, new_list->next);
		else if (new_list->next->type == T_SPACE)
			unlink_node(&new_list);
		else
			new_list = new_list->next;
	}
	new_list = *list;
}
//"hola" que tal "asdasd"patata
//tal ""