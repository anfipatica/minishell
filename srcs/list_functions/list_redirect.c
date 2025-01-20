#include "minishell.h"

/**
 * This function only prints the context of the list, useful for debugging
 */
// void	print_tokens(t_token *token)
// {
// 	int i;

// 	i = 1;
// 	dprintf(2, "\n╭━━━┈┈<⭒.⋆🪐 𝕊𝕋𝔸ℝ𝕋 ✨˚⋆.>┈┈━━━╮\n");
// 	while (token)
// 	{
// 		dprintf(2, "\n\033[44m╔═════════════════════════════╗\033[0m\n");
// 		dprintf(2, "\033[44m║       🚀 TOKEN Nº %-4d      ║\033[0m\n", i++);
// 		dprintf(2, "\033[44m╠═════════════════════════════╣\033[0m\n");
// 		dprintf(2, "\033[44m║💡  Type      :   %s        ║\033[0m\n", get_token_name(token->type));
// 		dprintf(2, "\033[44m║📜  String    :  →%s←       ║\033[0m\n", token->str);
// 		if(token->expanded != NULL)
// 			dprintf(2, "\033[44m║✨  Expand Var:  →%s←       ║\033[0m\n", token->expanded);
// 		dprintf(2, "\033[44m╚═════════════════════════════╝\033[0m\n");
// 		token = token->next;
// 	}
// 	dprintf(2, "\n╰☆┈☆┈☆┈☆┈< 🌙 𝐹𝐼𝒩 🌌 >┈☆┈☆┈☆┈☆╯\n\n");
// }

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

void	ft_free_one_redirect(t_redirect *redirect)
{
	if (!redirect)
		return ;
	free(redirect);
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
		ft_free_one_redirect(redirect);
		redirect = temp;
	}
}