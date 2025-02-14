
#include "minishell.h"


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

	//dprintf(2, "node1 = %s, node2 = %s\n", node1->str, node2->str);
	//node1->free_expanded = true;
	str_nodes = ft_strjoin(get_valid_string(node1), get_valid_string(node2));
	//dprintf(2, "desde join_tokens node1->expanded es null: %s\n", str_nodes);
	
	// dprintf(2, "jointokens\n");
	// dprintf(2, "dir expanded: %p\n", node1->expanded);
	// dprintf(2, "value expanded: %s\n", node1->expanded);
	if (node1->free_expanded  == true)
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
	t_token *space;

	space = (*before_space)->next;
	(*before_space)->next = (*before_space)->next->next;
	ft_free_one_node(space);
	(*before_space) = (*before_space)->next;

}

void	turn_to_word(t_token *token)
{
	if (token->type == T_S_QUOTE || token->type == T_D_QUOTE)
		token->type = T_WORD;
	if (token->type == T_ENV && token->expanded)
		token->type = T_WORD;
}

void	list_checker(t_token **list)
{
	t_token *new_list;
	t_token *next;

	new_list = *list;
	turn_to_word(new_list);
	while (new_list->next)
	{
		next = new_list->next;
		turn_to_word(next);
		if (new_list->type == T_WORD && next->type == T_WORD)
			join_tokens(new_list, next);
		else
			new_list = next;
	}
	new_list = *list;
	*list = check_and_delete_space(new_list);
	new_list = check_and_delete_env(*list, NULL);
	*list  = new_list;
}

/* void	list_checker(t_token **list)
{
	t_token *new_list;

	new_list = *list;
	while (new_list->next)
	{
		if (new_list->type == T_S_QUOTE || new_list->type == T_D_QUOTE)
			new_list->type = T_WORD;
		if (new_list->next && (new_list->next->type == T_S_QUOTE || new_list->next->type == T_D_QUOTE))
			new_list->next->type = T_WORD;
		if (new_list->type == T_WORD && new_list->next->type == T_WORD)
			join_tokens(new_list, new_list->next);
		else if (new_list->type == T_WORD && new_list->next->type == T_ENV)
			join_tokens(new_list, new_list->next);
		else if (new_list->type == T_ENV && new_list->next->type == T_WORD)
			join_tokens(new_list, new_list->next);
		else if (new_list->type == T_ENV && new_list->next->type == T_ENV)
			join_tokens(new_list, new_list->next);
		else
			new_list = new_list->next;
	}
	new_list = *list;
	*list = eval(new_list);
	*list = check_and_delete(new_list);
} */