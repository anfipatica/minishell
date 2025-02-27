
#include "minishell.h"

void	join_tokens(t_token *node1, t_token *node2)
{
	char	*str_nodes;
	t_token *aux;

	str_nodes = ft_strjoin(
		ft_ternary(node1->expanded, node1->expanded, node1->str),
		ft_ternary(node2->expanded, node2->expanded, node2->str));
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
}

t_token *create_new_node_by_env(t_token *env_node)
{
	t_token	*head;
	t_token	*new;
	char		**env_splitted;
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
	t_token *curr_node;
	t_token *next;

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
