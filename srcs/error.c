#include "minishell.h"

void	ft_perror(char *str)
{
	dprintf(2, "errno = %d\n", errno);
	if (str == NULL)
		write(2, "\"\": empty command\n", 19);
	else if ((str != NULL) && (errno != 0))
	{
		dprintf(2, "%s\n", str);
		perror(str);
	}
	else
	{
		write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 21);
	}
	//exit(1); ---------------- en caso de qeu se necesita lo ponemos
}

void	error_exit(char *str, int error)
{
	if (error == IS_DIR)
		dprintf(2, "%s: Is a directory\n", str);
	else if (error == COMMAND_NOT_FOUND)
		dprintf(2, "%s: command not found\n", str);
	else
		dprintf(2, "Unknown error\n");
}

