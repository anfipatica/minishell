#include "minishell.h"

bool	ft_strisdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (false);
	}
	return (true);
}


void ft_exit(t_command *command)
{
	int	i;

	i = 0;
	while(command->args)
	{

		if (ft_strisdigit(command->args->name) == false)
		{
			error_exit(command->args->name, EXIT_NON_DIGIT);
		}
		i++;
	}
	printf("FT_EXIT\n");
	printf("%u", (unsigned int) -1);
	exit(123);
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
