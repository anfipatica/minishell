#include "minishell.h"

//TODO Hacer un automata() que imite /printers/printers.c/print_states() sin imprimir.
//TODO en base a algún flag del makefile.

void	function_array_filler(int (*array_of_functions[])(t_backpack *))
{
	array_of_functions[0] = NULL;
	array_of_functions[1] = insert_args;
	array_of_functions[2] = insert_file;
	array_of_functions[3] = set_redirect_type;
	array_of_functions[4] = end_command;
	array_of_functions[5] = syntax_error;
}

void	pack_backpack(t_backpack *backpack, t_env *env)
{
	backpack->head_command = NULL;
	backpack->last_command = NULL;
	backpack->env = env;
}

t_command	*automata(t_token *token, t_env *env)
{
	t_backpack	backpack[1];
	int			current_state;
	int			(*function_array[6])(t_backpack *);

	current_state = 0;
	function_array_filler(function_array);
	pack_backpack(backpack, env);
	while (token)
	{
		backpack->token = token;
		current_state = get_new_state(current_state, token->type);
		if (function_array[current_state](backpack) == ERROR__STATE)
			return(NULL);
		token = token->next;
	}
	if (current_state > ACCEPT_STATES)
		return (syntax_error(backpack), NULL);
	return (backpack->head_command);
}

char *str_states[] = {
	"0 - estado inicial",
	"1 - estado flag - ACCEPT_STATE",
	"2 - estado file - ACCEPT_STATE",
	"3 - estado redirect",
	"4 - estado pipe",
	"5 - estado err - ERROR__STATE",
	NULL
};

int	get_new_state(int current_state, int token)
{
	// dprintf(2, "|  current_state: "BLUE"%d\033[0m - token: %d  |\n",current_state, token);

	const int	matrix[6][8] = { //--[ ]*****ESTADOS*****
		{1, 1, 3, 3, 3, 3, 3, 5}, //- 0 - estado inicial
		{1, 1, 3, 3, 3, 3, 3, 4}, //- 1 - estado flag - ACCEPT_STATE
		{1, 1, 3, 3, 3, 3, 3, 4}, //- 2 - estado file - ACCEPT_STATE
		{2, 2, 5, 5, 5, 5, 5, 5}, //- 3 - estado redirect
		{1, 1, 3, 3, 3, 3, 3, 5}, //- 4 - estado pipe
		{5, 5, 5, 5, 5, 5, 5, 5}  //- 5 - estado err - ERROR__STATE
};	//- |  |  |  |  |  |  |  |
	//- |  |  |  |  |  |  |  |
	//- W  $  <  << >  >> <> |      [ ][ ]TOKENS
//	printf("prev: %d new: %d text:[%s]\n", current_state, matrix[current_state][token], str_states[matrix[current_state][token]]);
	return (matrix[current_state][token]);
}

