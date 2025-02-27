/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:34:02 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/28 00:55:00 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_or_error(char **matrix[2], char *path_name, t_command *command)
{
	struct stat	buffer;

	if (!path_name || !path_name[0])
		return (error_exit(matrix[ARGS][0], COMMAND_NOT_FOUND, command));
	for (int i = 0; matrix[ARGS][i]; i++)
		printf("->%s\n", matrix[ARGS][i]);
	for (int i = 0; matrix[ENV][i]; i++)
		printf("->%s\n", matrix[ENV][i]);
	execve(path_name, matrix[ARGS], matrix[ENV]);
	if (stat(path_name, &buffer) == -1)
		ft_perror(matrix[ARGS][0]);
	else if ((buffer.st_mode & __S_IFMT) == __S_IFDIR)
		error_exit(path_name, IS_DIR, command);
	else
		ft_perror(matrix[ARGS][0]);
	exit(NO_PERMISSION);
}

bool	builtin_without_pipe(t_command *command)
{
	int	aux_stdout;
	int	aux_stdin;

	if (command->next)
		return (false);
	if (check_builtins(command) == false)
		return (false);
	aux_stdout = dup(OUT_FILE);
	aux_stdin = dup(IN_FILE);
	if (handle_files(command->head_redirect) == OPEN_ERROR)
	{
		g_exit_status = EXIT_STATUS_ERROR;
		restore_builtin_fds(aux_stdout, aux_stdin);
		return (true);
	}
	if (exec_builtin(command) == true)
	{
		restore_builtin_fds(aux_stdout, aux_stdin);
		return (true);
	}
	return (false);
}

void	begin_execution(t_command *command)
{
	if (!command)
		return ;
	if (find_heredoc(command) == SIGINT_SIGNAL)
		return ;
	if (g_exit_status == SIGINT_SIGNAL || builtin_without_pipe(command) == true)
		return ;
	daddy_executor(command);
}
