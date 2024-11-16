#include "minishell.h"

void	go_over_list(t_token *token)
{
	t_token	*temp;
	char *liberador;
	temp = token;
	int i;
	i = 0;
	printf("\n************START************\n\n");
	while (temp)
	{
		printf("__________________________\n");
		printf(">>>     TOKEN nº %d    <<<\n", i++);
		printf("￣￣￣￣￣￣￣￣￣￣￣￣￣\n");

		
		liberador = ft_substr(temp->str, 0, temp->length);
		printf("      type = %s\n", get_token_name(temp->type));
		printf("       str = %s\n", liberador);
		printf("expand var = %s\n\n", temp->expanded);
		temp = temp->next;
		free(liberador);
	}
	printf("***********FIN************\n");
}

t_token	*new_token(t_token_value type, char *str, int length)
{
	t_token	*new_token;

	new_token = (t_token *) malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->str = str;
	new_token->expanded = expandetor(str);
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
}

void	ft_free_list(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;
	free(token->str);
	while (token != NULL)
	{
		temp = token->next;
		free(token);
		token = temp;
	}
}