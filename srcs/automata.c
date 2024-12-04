#include "minishell.h"



//TODO Hacer un automata() que imite /printers/printers.c/print_states() sin imprimir.
//TODO en base a algún flag del makefile.




int	get_new_state(int current_state, int token)
{
	printf("|  current_state: "BLUE"%d\033[0m - token: %d  |\n",current_state, token);

	const int	matrix[5][10] = {	//-[ ]*****ESTADOS*****
		{1, 1, 1, 1, 1, 2, 2, 2, 2, 4},//- 0 - estado inicial
		{1, 1, 1, 1, 1, 2, 2, 2, 2, 3},//- 1 - estado words - ACCEPT_STATE
		{1, 1, 1, 1, 1, 4, 4, 4, 4, 4},//- 2 - estado redirects
		{1, 1, 1, 1, 1, 2, 2, 2, 2, 4},//- 3 - estado pipe
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4}	//- 4 - estado err - ERROR__STATE
	};// |  |	|  |  |	 |	|  |  |	 |
// 		 |  |	|  |  |	 |	|  |  |	 |
//-		 W  S  $  "  '  <  << >  >> | [ ][ ]TOKENS
	return (matrix[current_state][token]);
}

// [0][8] -> bash: syntax error near unexpected token `|'
// [2][4] -> bash: syntax error near unexpected token `<'
// [2][5] -> bash: syntax error near unexpected token `<<'
// [2][6] -> bash: syntax error near unexpected token `>'
// [2][7] -> bash: syntax error near unexpected token `>>'
// [2][8] -> bash: syntax error near unexpected token `|'