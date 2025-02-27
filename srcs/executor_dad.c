/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_dad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:53:18 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/27 22:19:43 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all(void)
{
	int		current_status;
	int		last_process_status;
	pid_t	current_wp;
	pid_t	last_wp;

	current_wp = 0;
	last_wp = 0;
	while (current_wp != ALL_CHILDREN_DEAD)
	{
		current_wp = waitpid(-1, &current_status, 0);
		if (current_wp > last_wp)
		{
			last_process_status = current_status;
			last_wp = current_wp;
		}
		if (WIFEXITED(last_process_status))
			g_exit_status = WEXITSTATUS(last_process_status);
		else if (WIFSIGNALED(last_process_status))
			g_exit_status = WTERMSIG(last_process_status) + 128;
	}
	signal(SIGQUIT, SIG_IGN);
}

int	daddy_executor(t_command *command)
{
	int		pipefd[2];
	int		in_fd;
	bool	multiple_commands;

	pipefd[0] = IN_FILE;
	pipefd[1] = OUT_FILE;
	in_fd = 0;
	multiple_commands = true;
	if (command->next == NULL)
		multiple_commands = false;
	while (command)
	{
		if (command->next)
			pipe(pipefd);
		exec_jr(command, in_fd, pipefd);
		restore_daddy_fds(multiple_commands, in_fd, pipefd);
		command = command->next;
	}
	if (multiple_commands == true)
		close(pipefd[IN_FILE]);
	wait_all();
	return (0);
}
