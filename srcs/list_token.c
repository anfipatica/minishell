#include "minishell.h"

/**
 * This function only prints the context of the list, useful for debugging
 */
void	print_tokens(t_token *token)
{
	int i;

	i = 1;
	printf("\n╭━━━┈┈<⭒.⋆🪐 𝕊𝕋𝔸ℝ𝕋 ✨˚⋆.>┈┈━━━╮\n");
	while (token)
	{
		printf("\n\033[44m╔═════════════════════════════╗\033[0m\n");
		printf("\033[44m║       🚀 TOKEN Nº %-4d      ║\033[0m\n", i++);
		printf("\033[44m╠═════════════════════════════╣\033[0m\n");
		printf("\033[44m║💡  Type      :   %s        ║\033[0m\n", get_token_name(token->type));
		printf("\033[44m║📜  String    :  →%s←       ║\033[0m\n", token->str);
		if(token->expanded)
			printf("\033[44m║✨  Expand Var:  →%s←       ║\033[0m\n", token->expanded);
		printf("\033[44m╚═════════════════════════════╝\033[0m\n");
		token = token->next;
	}
	printf("\n╰☆┈☆┈☆┈☆┈< 🌙 𝐹𝐼𝒩 🌌 >┈☆┈☆┈☆┈☆╯\n\n");
}

/**
 * new_token creates a new token and allocates memory for it.
 */
t_token	*new_token(t_token_value type, char *str, int length)
{
	t_token	*new_token;

	new_token = (t_token *) malloc(sizeof(t_token));
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
		free(token->str);
		if (token->free_expanded == true)
			free(token->expanded);
		temp = token->next;
		free(token);
		token = temp;
	}
}