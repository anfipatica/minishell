#include "minishell.h"



//TODO Hacer un automata() que imite /printers/printers.c/print_states() sin imprimir.
//TODO en base a algún flag del makefile.

void	create_function_arr(int (*func_arr[])(t_token *, t_command *))
{
	func_arr[0] = NULL;
	func_arr[1] = insert_command;
	func_arr[2] = insert_flag;
	func_arr[3] = insert_file;
	func_arr[4] = set_redirect_type;
	func_arr[5] = end_command;
	func_arr[6] = sintax_error;
}

t_command	*automata(t_token *token)
{
	t_command	*head_command;
	t_command	*command;
	int			current_state;
	int		(*func_arr[7])(t_token *, t_command *);

	command = NULL;
	current_state = 0;
	create_function_arr(func_arr);
	head_command = new_command();
	command = head_command;
	while (token)
	{
		printf("state = %d\n", current_state);
		current_state = get_new_state(current_state, token->type);
		if (func_arr[current_state](token, command) == ERROR__STATE)
			return (ft_free_commands(head_command), NULL);
		token = token->next;
	}
	if (current_state > ACCEPT_STATES)
		printf(RED"SINTAX_ERROR\n"STD);

	return (head_command);
}

int	get_new_state(int current_state, int token)
{
	printf("|  current_state: "BLUE"%d\033[0m - token: %d  |\n",current_state, token);

	const int	matrix[7][8] = { //-[ ]*****ESTADOS*****
		{1, 1, 4, 4, 4, 4, 4, 6},//- 0 - estado inicial
		{2, 2, 4, 4, 4, 4, 4, 5},//- 1 - estado command - ACCEPT_STATE
		{2, 2, 4, 4, 4, 4, 4, 5},//- 2 - estado flag - ACCEPT_STATE
		{1, 1, 4, 4, 4, 4, 4, 5},//- 3 - estado file - ACCEPT_STATE
		{3, 3, 6, 6, 6, 6, 6, 6},//- 4 - estado redirect
		{1, 1, 4, 4, 4, 4, 4, 6},//- 5 - estado pipe
		{6, 6, 6, 6, 6, 6, 6, 6} //- 6 - estado err - ERROR__STATE
	};// |  |  |  |  |  |  |  |
// 		 |  |  |  |  |  |  |  |
//-		 W  $  <  << >  >> <> |     [ ][ ]TOKENS
	return (matrix[current_state][token]);
}

