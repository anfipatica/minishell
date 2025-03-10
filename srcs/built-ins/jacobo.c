/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pepe copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:40:13 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/03/10 12:33:23 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	jacobo(void)
{
	const char	*cmd[] = {"/usr/bin/curl", "ascii.live/rick", NULL};
	int			pid;
	int			status;

	signal(SIGINT, child_signal_handler);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd[0], (char **)cmd, NULL);
		perror(cmd[0]);
		exit(1);
	}
	waitpid(pid, &status, 0);
	write(1, "\nHe perdido\n", 12);
}
