/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:21:37 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/03/05 17:34:51 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * To print errors with perror.
 */
void	ft_perror(char *str)
{
	if (str == NULL)
		write(2, "\"\": empty command\n", 19);
	else if ((str != NULL) && (errno != 0))
	{
		perror(str);
	}
}

/**
 * To print errors that require to exit and which messages are not included
 * in perror
 */
void	error_exit(char *str, int error_code, t_command *command)
{
	if (error_code == IS_DIR)
	{
		ft_putstr_fd(str, 2);
		write(2, ": Is a directory\n", 18);
	}
	else if (error_code == COMMAND_NOT_FOUND)
	{
		ft_putstr_fd(str, 2);
		write(2, ": command not found\n", 21);
	}
	else if (error_code == EXIT_NON_DIGIT)
	{
		ft_putstr_fd(str, 2);
		write(2, ": numeric argument required\n", 29);
	}
	else
		write(2, "unknown error\n", 14);
	free_all(command);
	exit(error_code);
}

/**
 * to print errors that are not included in perror that don't require to exit.
 */
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
