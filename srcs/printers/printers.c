#include "minishell.h"

/**
 * This function only prints the context of the list, useful for debugging
 */

void print_commands(t_command *command)
{
	t_args	*aux_args;
	t_redirect *aux_redirect;

	if (!command)
		return ;
	dprintf(2, "-----------------------------------------------\n");
	while (command)
	{
	aux_args = command->args;
	aux_redirect = command->head_redirect;
		while(aux_args)
		{
			dprintf(2, BLUE"args: %s\n"STD, aux_args->arg);
			aux_args = aux_args->next;
		}
		if (aux_redirect)
			dprintf(2, "- - - - - - - - - - - - - - - - - - - - - - - -\n");
		while(aux_redirect)
		{
			dprintf(2, PURPLE"redirect: %d - %s\n"STD, aux_redirect->redirect_type, aux_redirect->name);
			aux_redirect = aux_redirect->next;
		}
		dprintf(2, "-----------------------------------------------\n");
		command = command->next;
	}


}


void	print_tokens(t_token *token)
{
	int i;
	char strfield[100];

	i = 1;
	dprintf(2, "\n╭━━━┈┈<⭒.⋆🪐 𝕊𝕋𝔸ℝ𝕋 ✨˚⋆.>┈┈━━━╮\n");
	while (token)
	{
		dprintf(2, "\n\033[44m╔═════════════════════════════╗\033[0m\n");
		dprintf(2, "\033[44m║       🚀 TOKEN Nº %-4d      ║\033[0m\n", i++);
		dprintf(2, "\033[44m╠═════════════════════════════╣\033[0m\n");
		dprintf(2, "\033[44m║💡  Type      :   %-10s ║\033[0m\n", get_token_name(token->type));
		sprintf(strfield, "→%s←", token->str);
		dprintf(2, "\033[44m║📜  String    :  %-15s ║\033[0m\n", strfield);
		if(token->expanded != NULL)
			dprintf(2, "\033[44m║✨  Expand Var:  →%s←       ║\033[0m\n", token->expanded);
		dprintf(2, "\033[44m╚═════════════════════════════╝\033[0m\n");
		token = token->next;
	}
	dprintf(2, "\n╰☆┈☆┈☆┈☆┈< 🌙 𝐹𝐼𝒩 🌌 >┈☆┈☆┈☆┈☆╯\n\n");
}

int	print_states(t_token *token)
{
	int	current_state;

	current_state = 0;
dprintf(2, "\n╭━━━┈┈<⭒.⋆🤖 🅰🆄🆃🅾🅼🅰🆃🅰 🤖⋆>┈┈━━━━╮\n");
dprintf(2, "|                               |");


# define ORANG "\033[1;33m"

	dprintf(2, "\n|\033[33m       current_state = %d       \033[0m|\n", current_state);
	dprintf(2, "|                 "BLUE"╭┈┈┈┈┈╯\033[0m       |\n");

	while (token)
	{
		current_state =  get_new_state(current_state, token->type);
		token = token->next;
		if (current_state == ERROR__STATE)
		return (dprintf(2, "╰━━┈┈< ❌ "RED"Syntax error"STD" ❌  >┈┈━━╯\n"));
		dprintf(2, "|\033[33m       current_state = %d       \033[0m|\n", current_state);
		if (token)
			dprintf(2, "|                 "BLUE"╭┈┈┈┈┈╯\033[0m       |\n");
	}
	if (current_state != ACCEPT_STATES)
		return (dprintf(2, "╰━━┈┈< ❌ "RED"Syntax error"STD" ❌  >┈┈━━╯\n"));
	dprintf(2, "|                               |\n");
	dprintf(2, "╰━━━┈┈<⭒.⋆🔧🅰🆄🆃🅾🅼🅰🆃🅰 🔧⋆.⭒>┈┈━━━╯\n");

	return (0);
}