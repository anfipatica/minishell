#include "../inc/minishell.h"

void	go_over_list(t_token *token)
{
	t_token	*temp;

	temp = token;
	printf("-------------------------------\n");
	while (temp)
	{
		printf("type = %d, str = %s\n", temp->type, temp->str);
		temp = temp->next;
	}
	printf("-------------------------------\n");
}

t_token	*new_token(t_token_value type, char *str, int length)
{
	t_token	*new_token;

	new_token = (t_token *) malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->str = str;
	new_token->length = length;
	new_token->next = NULL;
	return (new_token);
}

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
	go_over_list(*lst);
}

void	ft_free_list(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;

	while (token != NULL)
	{
		
		temp = token->next;
		free(token->str);
		free(token);
		token = temp;
	}
}