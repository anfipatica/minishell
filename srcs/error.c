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
	{
		ft_putstr_fd(str, 2);
		write(2, ": Is a directory\n", 18);
		exit(126);
	}
	if (error == NO_PERMISSION)
	{
		ft_putstr_fd(str, 2);
		write(2, ": Permission denied\n", 21);
		exit(126);
	}
	else if (error == COMMAND_NOT_FOUND)
	{
		ft_putstr_fd(str, 2);
		write(2, ": command not found\n", 21);
		exit(127);
	}

	else
		write(2, "unknown error\n", 14);
}

void	print_error(char *str, int error)
{
	if (error == INVALID_EXPORT_IDENTIFIER)
	{
		write(2, "export: `", 9);
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n", 26);
	}
	else
		write(2, "unknown error\n", 14);
}

