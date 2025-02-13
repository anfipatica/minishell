/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dokeitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:52:31 by psapio            #+#    #+#             */
/*   Updated: 2025/02/13 18:46:48 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*filename_generator(void)
{
	static int	index_filename = 0;
	char *file_temp;
	char *number_conv;
	
	number_conv = ft_itoa(index_filename++);
	if(!number_conv)
		return (NULL);
	file_temp = ft_strjoin("/tmp/tempfile", number_conv);
	free(number_conv);
	return (file_temp); //!LIBERAR AL FINAL DE LA EJECUCIÓN.
}

char *here_dokeitor(char *limiter, char *new_temp_file)
{
	int	heredoc_fd;
	char	*input_line;
	pid_t	family;
	int		status;

	if (!new_temp_file)
		return (NULL);
	heredoc_fd = open(new_temp_file, O_WRONLY | O_CREAT | O_TRUNC, STD_PERMISSIONS);
	if (heredoc_fd == -1)
		return (unlink(new_temp_file), NULL);
	family = fork();
	if (family == CHILD)
	{
		printf("->%s\n", limiter);
		signal(SIGINT, heredoc_signal_handler);
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
		close(heredoc_fd);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	wait(&status);
	g_exit_status = WEXITSTATUS(status);
	close(heredoc_fd);
	return (new_temp_file);
}

void	find_heredoc(t_command *command)
{
	t_redirect	*file;

	while (command && g_exit_status != SIGINT_SIGNAL)
	{
		file = command->head_redirect;
		while (file && g_exit_status != SIGINT_SIGNAL)
		{
			if (file->redirect_type == T_HERE_DOC)
				file->name = here_dokeitor(file->name, filename_generator());
			file = file->next;
		}
		command = command->next;
	}
}
/*
	cat << a << b << c | cat << 1 < que << 2 << 3 > out

  token1
	cat
	lista de red
		here - here_1 
		here - here_2
		here - here_3
		
	cat
	lista de red
		here - here_4
		in   - que
		here - here_5
		here - here_6
		out  - 4

*/

/*
	cat << a << b << c | cat << 1 < que << 2 << 3 > out

  token1
	cat
	lista de red
		here - a
		here - b
		here - c
		
	cat
	lista de red
		here - 1
		in   - que
		here - 2
		here - 3
		out  - 4

*/