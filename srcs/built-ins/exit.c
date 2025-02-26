#include "minishell.h"

bool	ft_strisdigit(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (false);
	}
	return (true);
}

long	ft_atol(const char *nptr)
{
	int	i;
	long	sign;
	long	conversion;

	i = 0;
	sign = 1;
	conversion = 0;
	while ((nptr[i] == ' ') || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while ((nptr[i] != '\0') && ((nptr[i] >= '0') && (nptr[i] <= '9')))
	{
		conversion = conversion * 10;
		conversion = conversion + nptr[i] - '0';
		i++;
	}
	conversion = conversion * sign;
	return (conversion);
}

char	*ft_ltoa(long n)
{
	char		*array;
	int			counter;
	long int	n_twin;

	n_twin = (long int)n;
	counter = 0;
	if ((long int)n <= 0)
		counter++;
	while ((n_twin != 0) && counter++ >= 0)
		n_twin = n_twin / 10;
	array = ft_calloc(counter + 1, sizeof(char));
	if (array == NULL)
		return (NULL);
	n_twin = (long int)n;
	if ((long int)n < 0)
		(n_twin = (long int)n * -1);
	while (counter-- != 0)
	{
		array[counter] = n_twin % 10 + '0';
		n_twin = n_twin / 10;
	}
	if ((long int)n < 0)
		array[0] = '-';
	return (array);
}

bool does_overflow_unsigned_int(char *max_number)
{
	char *max_num_changed;

	max_num_changed = ft_ltoa(ft_atol(max_number));
	if (ft_strcmp(max_number, max_num_changed) == 0)
	{
		free(max_num_changed);
		return (false); 
	}
	free(max_num_changed);
	return (true);
}
//9223372036854775807 WOAAAAAAAAAAA
void ft_exit(t_command *command)
{
	t_args	*aux_head;
	int		return_number;
	
	aux_head = command->args;
	print_commands(command);
	command->args = command->args->next;
	if (ft_strisdigit(command->args->name) == false || does_overflow_unsigned_int(command->args->name) == true)
	{
		ft_free_one_args(aux_head);
		error_exit(command->args->name, EXIT_NON_DIGIT, command);
	}
	else if ((ft_strisdigit(command->args->name) == true && command->args->next != NULL))
	{
		write(2, "exit: too many arguments\n", 26);
		ft_free_one_args(aux_head);
		return ;
	}
	else
	{
		return_number = ft_atoi(command->args->name);
		// command->args = command->args->next;
		command->args = aux_head;
		free_all(command);
		printf("%d\n", return_number);
		exit((unsigned char)return_number);
	}
}

/*
sale
exit asd asd
exit
exit: asd: numeric argument required 2

no sale
exit 123 123 / exit 123 asd
exit
bash: exit: too many arguments 1

*/
