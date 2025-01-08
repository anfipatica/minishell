#include "minishell.h"

/**
 * This function only prints the context of the list, useful for debugging
 */
// void	print_tokens(t_token *token)
// {
// 	int i;

// 	i = 1;
// 	printf("\n╭━━━┈┈<⭒.⋆🪐 𝕊𝕋𝔸ℝ𝕋 ✨˚⋆.>┈┈━━━╮\n");
// 	while (token)
// 	{
// 		printf("\n\033[44m╔═════════════════════════════╗\033[0m\n");
// 		printf("\033[44m║       🚀 TOKEN Nº %-4d      ║\033[0m\n", i++);
// 		printf("\033[44m╠═════════════════════════════╣\033[0m\n");
// 		printf("\033[44m║💡  Type      :   %s        ║\033[0m\n", get_token_name(token->type));
// 		printf("\033[44m║📜  String    :  →%s←       ║\033[0m\n", token->str);
// 		if(token->expanded != NULL)
// 			printf("\033[44m║✨  Expand Var:  →%s←       ║\033[0m\n", token->expanded);
// 		printf("\033[44m╚═════════════════════════════╝\033[0m\n");
// 		token = token->next;
// 	}
// 	printf("\n╰☆┈☆┈☆┈☆┈< 🌙 𝐹𝐼𝒩 🌌 >┈☆┈☆┈☆┈☆╯\n\n");
// }

/**
 * new_token creates a new token and allocates memory for it.
 */
t_command	*new_command(t_env *env)
{
	t_command	*new_command;

	new_command = (t_command *) malloc(sizeof(t_command));
	if (!new_command)
		return (NULL);
	new_command->path_command = NULL;
	new_command->args = NULL;
	new_command->redirect = NULL;
	new_command->env = env;
	new_command->next = NULL;
	return (new_command);
}

/**
 * add_command_back receives the head of the list and the new command
 * to add at the end of said list. If there is no head, new becomes it.
 */
void	add_command_back(t_command **lst, t_command *new)
{
	t_command	*temp;

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

void	ft_free_one_command(t_command *command)
{
	if (!command)
		return ;
	free(command->path_command);
	//free_args matrix
	//free_redirect struct
	free(command);
}

/**
 poi uscire * ft_free_commands frees the nodes of a list and the neccesary content
 * inside each of them.
 */
void	ft_free_commands(t_command *command)
{
	t_command	*temp;

	if (!command)
		return ;
	while (command != NULL)
	{
		temp = command->next;
		ft_free_one_command(command);
		command = temp;
	}
}