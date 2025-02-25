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
	int			i;
	t_args	*aux_head;

	aux_head = command->args;
	i = 0;
	print_commands(command);
	command->args = command->args->next;
	while(command->args)
	{

		if (ft_strisdigit(command->args->name) == false)
		{
			command->args = aux_head;
			ft_free_env(command->env);
			ft_free_tokens(command->token_pointer);
			ft_free_commands(command);
			error_exit(command->args->name, EXIT_NON_DIGIT);
		}
		else if ((ft_strisdigit(command->args->name) == true && command->args->next != NULL))
		{
			write(2, "exit: too many arguments\n", 26);
			return ;
		}
		i++;

		command->args = command->args->next;

	}
	command->args = aux_head;
	ft_free_env(command->env);
	ft_free_tokens(command->token_pointer);
	ft_free_commands(command);
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
