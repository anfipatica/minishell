#include "minishell.h"

int	print_states(t_token *token)
{
	int	current_state;

	current_state = 0;
	printf("\n╭━━━┈┈<⭒.⋆🪐 𝕊𝕋𝔸ℝ𝕋 ✨˚⋆.>┈┈━━━╮\n");
	printf("current_state = %d\n", current_state);
	while (token)
	{
		current_state =  get_new_state(current_state, token->type);
		token = token->next;
		if (current_state == ERROR__STATE)
			return (printf(RED"Syntax error\n"STD));
		printf("current_state = %d\n", current_state);
	}
	if (current_state != ACCEPT_STATE)
		return (printf(RED"Syntax error\n"STD));
	printf("\n╰☆┈☆┈☆┈☆┈< 🌙 𝐹𝐼𝒩 🌌 >┈☆┈☆┈☆┈☆╯\n\n");
	return (0);
}

int	get_new_state(int current_state, int token)
{
	printf("%d - %d\n",current_state, token);
	const int	matrix[5][9] = {		//-   ***ESTADOS***
		{1, 1, 1, 1, 2, 2, 2, 2, 4},	//- 0.estado inicial
		{1, 1, 1, 1, 2, 2, 2, 2, 3},	//- 1.estado words
		{1, 1, 1, 1, 4, 4, 4, 4, 4},	//- 2.estado redirects
		{1, 1, 1, 1, 2, 2, 2, 2, 4},	//- 3.estado pipe
		{4, 4, 4, 4, 4, 4, 4, 4, 4}		//- 4.estado err
	};//-W  $  "  '  <  << >  >> | TOKENS
	return (matrix[current_state][token]);
}

// [0][8] -> bash: syntax error near unexpected token `|'
// [2][4] -> bash: syntax error near unexpected token `<'
// [2][5] -> bash: syntax error near unexpected token `<<'
// [2][6] -> bash: syntax error near unexpected token `>'
// [2][7] -> bash: syntax error near unexpected token `>>'
// [2][8] -> bash: syntax error near unexpected token `|'