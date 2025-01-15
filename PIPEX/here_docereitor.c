// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   here_docereitor.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: psapio <marvin@42.fr>                      +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/07/04 17:52:31 by psapio            #+#    #+#             */
// /*   Updated: 2024/07/08 11:58:19 by psapio           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "pipex.h"

// char	*here_dokeitor(char *limiter)
// {
// 	int		fd_doc;
// 	char	*input_line;
// 	char	*limiter_nl;

// 	limiter_nl = ft_strjoin(limiter, "\n");
// 	fd_doc = open("/tmp/tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (fd_doc == -1)
// 		return (unlink("/tmp/tempfile"), NULL);
// 	while (1)
// 	{
// 		write(1, "heredoc> ", 9);
// 		input_line = get_next_line(0);
// 		if (input_line == NULL || ft_strcmp(limiter_nl, input_line) == 0)
// 		{
// 			free(limiter_nl);
// 			free(input_line);
// 			break ;
// 		}
// 		write(fd_doc, input_line, ft_strlen(input_line));
// 		free(input_line);
// 	}
// 	close(fd_doc);
// 	return ("/tmp/tempfile");
// }
// /*
// void terminator_here_doc(int fd)
// {
// 	close(fd_doc);
// 	unlink("/tmp/tempfile");
// }
// */
