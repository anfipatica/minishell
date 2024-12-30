#include "minishell.h"

/**
 * This function only prints the context of the list, useful for debugging
 */
void	print_tokens(void *content)
{
	t_token	*token = (t_token *)content;
	static int i;

	// printf("\n╭━━━┈┈<⭒.⋆🪐 𝕊𝕋𝔸ℝ𝕋 ✨˚⋆.>┈┈━━━╮\n");
	// while (token)
	// {
	printf("\n\033[44m╔═════════════════════════════╗\033[0m\n");
	printf("\033[44m║       🚀 TOKEN Nº %-4d      ║\033[0m\n", i++);
	printf("\033[44m╠═════════════════════════════╣\033[0m\n");
	printf("\033[44m║💡  Type      :   %s        ║\033[0m\n", get_token_name(token->type));
	printf("\033[44m║📜  String    :  →%s←       ║\033[0m\n", token->str);
	if(token->expanded != NULL)
		printf("\033[44m║✨  Expand Var:  →%s←       ║\033[0m\n", token->expanded);
	printf("\033[44m╚═════════════════════════════╝\033[0m\n");
	// }
	// printf("\n╰☆┈☆┈☆┈☆┈< 🌙 𝐹𝐼𝒩 🌌 >┈☆┈☆┈☆┈☆╯\n\n");
}

// int	print_states(t_token *token)
// {
// 	int	current_state;

// 	current_state = 0;
// printf("\n╭━━━┈┈<⭒.⋆🤖 🅰🆄🆃🅾🅼🅰🆃🅰 🤖⋆>┈┈━━━━╮\n");
// printf("|                               |");


// # define ORANG "\033[1;33m"

// 	printf("\n|\033[33m       current_state = %d       \033[0m|\n", current_state);
// 	printf("|                 "BLUE"╭┈┈┈┈┈╯\033[0m       |\n");

// 	while (token)
// 	{
// 		current_state =  get_new_state(current_state, token->type);
// 		token = token->next;
// 		if (current_state == ERROR__STATE)
// 		return (printf("╰━━┈┈< ❌ "RED"Syntax error"STD" ❌  >┈┈━━╯\n"));
// 		printf("|\033[33m       current_state = %d       \033[0m|\n", current_state);
// 		if (token)
// 			printf("|                 "BLUE"╭┈┈┈┈┈╯\033[0m       |\n");
// 	}
// 	if (current_state != ACCEPT_STATES)
// 		return (printf("╰━━┈┈< ❌ "RED"Syntax error"STD" ❌  >┈┈━━╯\n"));
// 	printf("|                               |\n");
// 	printf("╰━━━┈┈<⭒.⋆🔧🅰🆄🆃🅾🅼🅰🆃🅰 🔧⋆.⭒>┈┈━━━╯\n");

// 	return (0);
// }