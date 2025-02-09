#include "minishell.h"

void ft_exit(t_command *command)
{
	(void)command;
	printf("FT_EXIT\n");
	exit(123);
}
