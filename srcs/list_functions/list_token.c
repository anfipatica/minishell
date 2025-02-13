#include "minishell.h"


/**
 * new_token creates a new token and allocates memory for it.
 */
t_token	*new_token(e_token_value type, char *str, int length)
{
	t_token	*new_token;

	new_token = (t_token *) ft_calloc(sizeof(t_token), 1);
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->str = ft_substr(str, 0 , length); // aqui habia fallo... teneiamos que crear un substring ya que vamo a liberar esta variabble!!
	new_token->length = length;
	if (type == T_S_QUOTE)
	{
		new_token->expanded = ft_substr(str, 1, length - 2);
		new_token->free_expanded = true;
	}
	else
	{
		new_token->expanded = NULL;
		new_token->free_expanded = false;
	}
	new_token->next = NULL;
	return (new_token);
}

/**
 * add_token_back receives the head of the list and the new token
 * to add at the end of said list. If there is no head, new becomes it.
 */
void	add_token_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_free_one_node(t_token *token)
{
	if (!token)
		return ;
	free(token->str);
	token->str = NULL;
	if (token->free_expanded == true)
	{
		free(token->expanded);
		token->expanded = NULL;
	}
	free(token);
}
/**
 * ft_free_tokens frees the nodes of a list and the neccesary content
 * inside each of them.
 */
void	ft_free_tokens(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;
	while (token != NULL)
	{
		temp = token->next;
		ft_free_one_node(token);
		token = temp;
	}
}

t_token *check_and_delete_space(t_token *lst)
{
	t_token *result = NULL;

	if (!lst)
		return NULL;

	lst->next = check_and_delete_space(lst->next);

	if (lst->type == T_SPACE)
	{
		result = lst->next;
		ft_free_one_node(lst);
	}
	else
		result = lst;
	return (result);
}

t_token *check_and_delete_env(t_token *lst, t_token *lst_prev)
{
	t_token *result;

	result = NULL;
	if (!lst_prev && (lst->type == T_ENV && !(lst->expanded)))
		return (ft_free_one_node(lst), NULL);
	if (!lst)
		return NULL;
	lst->next = check_and_delete_env(lst->next, lst);
	if (lst->type == T_WORD && lst_prev && lst_prev->type ==  T_HERE_DOC)
	{
		lst->str = ft_strchrtrim(lst->str, '\"');
		result = lst;
	}
	else if (lst->type == T_ENV &&
		!(lst->expanded) && (lst_prev) && lst_prev->type != T_HERE_DOC)
	{
		result = lst->next;
		ft_free_one_node(lst);
	}
	else
		result = lst;
	return (result);
}

/* void	ft_lstdel(t_token **lst, void *context, bool (*predicate)(void *, void *), void (*del)(void *))
{
	*lst = eval(*lst, context, predicate, del);
} */
