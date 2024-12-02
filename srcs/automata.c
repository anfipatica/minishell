#include "minishell.h"

int	print_states(t_token *token)
{
	int	current_state;

	current_state = 0;
printf("\n╭━━━┈┈<⭒.⋆🤖 🅰🆄🆃🅾🅼🅰🆃🅰 🤖⋆>┈┈━━━━╮\n");
printf("|                               |");


# define ORANG "\033[1;33m"

	printf("\n|\033[33m       current_state = %d       \033[0m|\n", current_state);
	printf("|                 "BLUE"╭┈┈┈┈┈╯\033[0m       |\n");

	while (token)
	{
		current_state =  get_new_state(current_state, token->type);
		token = token->next;
		if (current_state == ERROR__STATE)
		return (printf("╰━━┈┈< ❌ "RED"Syntax error"STD" ❌  >┈┈━━╯\n"));
		printf("|\033[33m       current_state = %d       \033[0m|\n", current_state);
		if (token)
			printf("|                 "BLUE"╭┈┈┈┈┈╯\033[0m       |\n");
	}
	if (current_state != ACCEPT_STATE)
		return (printf("╰━━┈┈< ❌ "RED"Syntax error"STD" ❌  >┈┈━━╯\n"));
	printf("|                               |\n");
	printf("╰━━━┈┈<⭒.⋆🔧🅰🆄🆃🅾🅼🅰🆃🅰 🔧⋆.⭒>┈┈━━━╯\n");

	return (0);
}

int	get_new_state(int current_state, int token)
{
	printf("|  current_state: "BLUE"%d\033[0m - token: %d  |\n",current_state, token);

	const int	matrix[5][9] = {	//-[ ]*****ESTADOS*****
		{1, 1, 1, 1, 2, 2, 2, 2, 4},//- 0 - estado inicial
		{1, 1, 1, 1, 2, 2, 2, 2, 3},//- 1 - estado words - ACCEPT_STATE
		{1, 1, 1, 1, 4, 4, 4, 4, 4},//- 2 - estado redirects
		{1, 1, 1, 1, 2, 2, 2, 2, 4},//- 3 - estado pipe
		{4, 4, 4, 4, 4, 4, 4, 4, 4}	//- 4 - estado err - ERROR__STATE
	};// |	|  |  |	 |	|  |  |	 |
// 		 |	|  |  |	 |	|  |  |	 |
//-		 W  $  "  '  <  << >  >> | [ ][ ]TOKENS
	return (matrix[current_state][token]);
}

// [0][8] -> bash: syntax error near unexpected token `|'
// [2][4] -> bash: syntax error near unexpected token `<'
// [2][5] -> bash: syntax error near unexpected token `<<'
// [2][6] -> bash: syntax error near unexpected token `>'
// [2][7] -> bash: syntax error near unexpected token `>>'
// [2][8] -> bash: syntax error near unexpected token `|'