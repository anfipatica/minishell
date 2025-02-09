#include "minishell.h"


int	get_echo_state(int current_state, int echo_char)
{
	const int matrix[][4] = {
		{1, 3, 3}, //- 0 - estado inicial
		{3, 2, 3}, //- 1 - estado guion
		{3, 2, 3}, //- 2 - estado n
		{3, 3, 3}  //- 3 - estado err - ERROR__STATE
	};// -  n err 
    //-  0  1  2

	return (matrix[current_state][echo_char]);
}


int convert_char_to_echo_char(char c)
{
	if (c == '-')
		return (0);
	if (c == 'n')
		return (1);
	return (2);
}

int get_echo_flag(char *str)
{
	int	i = 0;
	int	state = 0;
	int echo_char;
	
	while (str[i])
	{
		echo_char = convert_char_to_echo_char(str[i]);
		state = get_echo_state(state, echo_char);
		i++;
	}
	if (state == 2)
		return (true);
	return (false);
	
}

//! TODOOOOOOOO esto es una movida jajaja
void ft_echo(t_command *command)
{
	(void)command;
	printf("FT_ECHO\n");
	bool real_echo_flag;
	bool new_echo_flag;
	char *str;
	t_args *aux_args = command->args;

	real_echo_flag = true;
	new_echo_flag = false;
	aux_args = aux_args->next;
	while (aux_args != NULL)
	{
		str = aux_args->name;
		if (real_echo_flag == false)
			new_echo_flag = get_echo_flag(str);
		if (new_echo_flag == false && real_echo_flag == true)
			ft_putstr_fd(str, 1);
		aux_args = aux_args->next;
	}
	if (real_echo_flag == 0)
		write(1, "\n", 1);
}

/* 
-n
error

real = 1
new = 0

echo -n algo -> algo%
echo -nnnnn -> %
echo -n -n -n -n -n -> %
echo -nnn -n -nn hola -n -> hola -n%
echo hola -n  -nnn -> hola -n  -nnn\n
*/