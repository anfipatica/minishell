/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docereitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:52:31 by psapio            #+#    #+#             */
/*   Updated: 2025/01/22 18:09:28 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// list_heredoc_in_command(t_command *command)
// {
	
// }



char	*filename_generator(void)
{
	static int	index_filename;

	return (ft_strjoin("/tmp/filetemp", ft_itoa(index_filename))); //!despuees habra que liberar
}




char *here_dokeitor(char *limiter, char *new_temp_file)
{
	int		heredoc_fd;
	char	*input_line;

	heredoc_fd = open(new_temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (heredoc_fd == -1)
		return (unlink(new_temp_file), OPEN_ERROR);
	while (1)
 	{
 		input_line = readline("> ");
 		if (input_line == NULL || ft_strcmp(limiter, input_line) == 0)
 		{
 			free(input_line);
 			break ;
 		}
 		write(heredoc_fd, input_line, ft_strlen(input_line));
		write(heredoc_fd, "\n", 1);
 		free(input_line);
 	}

	return (new_temp_file);
}



//esta funcion recibe la lista y 
//devuelve el ultimo fd del rispectivo heredoc 
char *find_heredoc(t_redirect *file)
{
	char *last_heredoc;
	
	dprintf(2, "file->name: %s\n", file->name);
	while(file)
	{
		if (file->redirect_type == T_HERE_DOC)
			last_heredoc = here_dokeitor(file->name, filename_generator());
		file->name = last_heredoc;
		file = file->next;
	}
	return(last_heredoc);
}
