/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:34:43 by psapio            #+#    #+#             */
/*   Updated: 2025/03/04 17:04:57 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_signal_handler(int signal)
{
	(void)signal;
	g_exit_status = SIGINT_SIGNAL;
	write(1, "\n", 1);
}

void	heredoc_signal_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	exit(130);
}

void	father_signal_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", false);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = SIGINT_SIGNAL;
}
