#include "minishell.h"

void	ft_perror(char *str)
{
	printf("errno = %d\n", errno);
	if (str == NULL)
		write(2, "\"\": empty command\n", 19);
	else if ((str != NULL) && (errno != 0))
	{
		printf("%s\n", str);
		printf("Sdasdasdasd\n");
		perror(str);
	}
	else
	{
		write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 21);
	}
	exit(1);
}

void	error_exit(char *str, int error)
{
	if (error == IS_DIR)
		printf("%s: Is a directory\n", str);
	else if (error == COMMAND_DOESNT_EXIST)
		printf("%s: command not found\n", str);
	else
		printf("Unknown error\n");
}

