
#include "minishell.h"

/**
 * new_token creates a new token and allocates memory for it.
 */
t_redirect	*new_redirect(e_token_value redirect_type)
{
	t_redirect	*new_redirect;

	new_redirect = (t_redirect *) malloc(sizeof(t_redirect));
	if (!new_redirect)
		return (NULL);
	new_redirect->name = NULL;
	new_redirect->redirect_type = redirect_type;
	new_redirect->next = NULL; 
	return (new_redirect);
}

/**
 * add_redirect_back receives the head of the list and the new redirect
 * to add at the end of said list. If there is no head, new becomes it.
 */
void	add_redirect_back(t_redirect **lst, t_redirect *new)
{
	t_redirect	*temp;

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

/**
 * ft_free_redirects frees the nodes of a list and the neccesary content
 * inside each of them.
 */
void	ft_free_redirects(t_redirect *redirect)
{
	t_redirect	*temp;

	if (!redirect)
		return ;
	while (redirect != NULL)
	{
		temp = redirect->next;
		if (redirect->redirect_type == T_HERE_DOC)
			free(redirect->name);
		free(redirect);
		redirect = temp;
	}
}