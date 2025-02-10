#include "minishell.h"
#define ERROR_FLAG 3
#define FLAG_OK 2

int	get_echo_state(int current_state, int echo_char)
{
	const int matrix[][4] = {
		{1, 3, 3}, //- 0 - estado inicial
		{3, 2, 3}, //- 1 - estado guion
		{3, 2, 3}, //- 2 - estado n
		{3, 3, 3}  //- 3 - estado err - ERROR__STATE
	};//-  n err 
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

bool get_echo_flag(char *str)
{
	int	i = 0;
	int	state = 0;
	int echo_char;
	
	while (str[i])
	{
		echo_char = convert_char_to_echo_char(str[i]);
		state = get_echo_state(state, echo_char);
		if (state == ERROR_FLAG)
			break ;
		i++;
	}
	if (state == FLAG_OK)
		return (true);
	return (false);
	
}

void ft_echo(t_command *command)
{
	int	total_flags;
	bool	flag;
	t_args *aux_args;
	
	aux_args = command->args->next;
	total_flags = 0;
	while (aux_args != NULL)
	{
		flag = get_echo_flag(aux_args->name);
		if (flag == true)
			total_flags += 1;
		else
			break;
		aux_args = aux_args->next;
	}
	while (aux_args != NULL)
	{
		printf("%s", aux_args->name);
		if (aux_args->next != NULL)
			printf(" ");
		aux_args = aux_args->next;
	}
	if (total_flags == 0)
		printf("\n");
}
