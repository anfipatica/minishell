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
	return (new_token);
}

void	ft_free_one_token(void *content)
{
	t_token *token;
	if (!content)
		return ;
	
	token = (t_token *) content;
	free(token->str);
	if (token->free_expanded == true)
	{
		free(token->expanded);
	}
	free(token);
}
