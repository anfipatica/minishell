#include "minishell.h"

//TODO Hacer un automata() que imite /printers/printers.c/print_states() sin imprimir.
//TODO en base a algún flag del makefile.

void	function_array_filler(int (*array_of_functions[])(t_token *token, t_command *command))
{
	array_of_functions[0] = NULL;
	array_of_functions[1] = insert_args;
	array_of_functions[2] = insert_file;
	array_of_functions[3] = set_redirect_type;
	array_of_functions[4] = end_command;
	array_of_functions[5] = sintax_error;
}



t_command	*automata(t_token *token, t_env *env)
{
	t_command	*head_command;
	t_command	*command;
	int			current_state;
	int			(*array_of_functions[6])(t_token *token, t_command *command);

	if (!token)
		return (NULL);

	head_command = NULL;
	command = new_command(env);
	//len_command_list(head_command);
	current_state = 0;
	function_array_filler(array_of_functions);
	while (token)
	{
		current_state = get_new_state(current_state, token->type);
		if (current_state == PIPE_STATE)
		{
			add_command_back(&head_command, command);
			command = new_command(env);
		}
		if (array_of_functions[current_state](token, command) == ERROR__STATE)
			return (ft_free_one_command(command), ft_free_commands(head_command), NULL);
		token = token->next;
	}
	add_command_back(&head_command, command);
	if (current_state > ACCEPT_STATES)
		return (write(2, RED"SINTAX_ERROR\n"STD, 28), ft_free_commands(head_command), NULL);
	return (head_command);
}

/* 
char *str_states[] = {
	"0 - estado inicial",
	"1 - estado flag - ACCEPT_STATE",
	"2 - estado file - ACCEPT_STATE",
	"3 - estado redirect",
	"4 - estado pipe",
	"5 - estado err - ERROR__STATE",
	NULL
};
 */

int	get_new_state(int current_state, int token)
{
	const int	matrix[6][8] = { //--[ ]*****ESTADOS*****
		{1, 1, 3, 3, 3, 3, 3, 5}, //- 0 - estado inicial
		{1, 1, 3, 3, 3, 3, 3, 4}, //- 1 - estado flag - ACCEPT_STATE
		{1, 1, 3, 3, 3, 3, 3, 4}, //- 2 - estado file - ACCEPT_STATE
		{2, 2, 5, 5, 5, 5, 5, 5}, //- 3 - estado redirect
		{1, 1, 3, 3, 3, 3, 3, 5}, //- 4 - estado pipe
		{5, 5, 5, 5, 5, 5, 5, 5}  //- 5 - estado err - ERROR__STATE
};	//-  |  |  |  |  |  |  |  |
	//-  |  |  |  |  |  |  |  |
	//-	 W  $  <  << >  >> <> |      [ ][ ]TOKENS
	//printf("prev: %d new: %d text:[%s]\n", current_state, matrix[current_state][token], str_states[matrix[current_state][token]]);
	return (matrix[current_state][token]);
}

