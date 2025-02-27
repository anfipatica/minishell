/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_jr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:50:02 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/28 00:49:03 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_jr_fd_handler(t_command *command, int in_fd, int *pipefd)
{
	if (in_fd != NULL_FD)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if (command->next)
	{
		close(pipefd[IN_FILE]);
		dup2(pipefd[OUT_FILE], 1);
		close(pipefd[OUT_FILE]);
	}
	if (handle_files(command->head_redirect) == OPEN_ERROR)
		exit(1);
}

void	exec_jr(t_command *command, int in_fd, int *pipefd)
{
	char	**matrix[2];
	char	*path_name;
	pid_t	family;

	ft_memset(matrix, 0, sizeof(matrix));
	command->execve_matrix = matrix;
	family = fork();
	if (family == CHILD)
	{
		signal(SIGQUIT, SIG_DFL);
		exec_jr_fd_handler(command, in_fd, pipefd);
		if (exec_builtin(command) == true)
			exit(g_exit_status);
		matrix_filler(command, matrix);
		path_name = find_path_name(matrix[ARGS][0], matrix[ENV], matrix[ARGS]);
		execute_or_error(matrix, path_name, command);
	}
	signal(SIGQUIT, child_signal_handler);
	signal(SIGINT, child_signal_handler);
}
