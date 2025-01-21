/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docereitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:52:31 by psapio            #+#    #+#             */
/*   Updated: 2025/01/21 14:28:13 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int here_dokeitor(char *limiter)
{
	dprintf(2, "limiter: %s\n", limiter);
	int		heredoc_fd;
	char	*input_line;
	char	*limiter_nl;

	heredoc_fd = open("/tmp/tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (heredoc_fd == -1)
		return (unlink("/tmp/tempfile"), OPEN_ERROR);
	while (1)
 	{
 		input_line = readline("> ");

		dprintf(2, "limiter: %s, input_line: %s\n", limiter, input_line);
 		if (input_line == NULL || ft_strcmp(limiter, input_line) == 0)
 		{
 			free(input_line);
 			break ;
 		}
 		write(heredoc_fd, input_line, ft_strlen(input_line));
		write(heredoc_fd, "\n", 1);
 		free(input_line);
 	}

	return (heredoc_fd);
}