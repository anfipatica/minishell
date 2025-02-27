/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dokeitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:52:31 by psapio            #+#    #+#             */
/*   Updated: 2025/02/28 00:12:49 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc_expanded(char *line, int heredoc_fd, t_env *env)
{
	int		i;
	int		j;
	char	*expanded_var;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] != '$')
		{
			while (line[i + j] && !ft_strchr(SPACES, line[i + j]))
				j++;
			expanded_var = ft_getenv(&line[i + 1], env, j - 1);
			write(heredoc_fd, expanded_var, ft_strlen(expanded_var));
			free(expanded_var);
			i += j;
			j = 0;
		}
		else
			write(heredoc_fd, &line[i++], 1);
	}
}

//eof = heredoc delimiter. Thanks norminette.
void	while_write_heredoc(char *eof, char *eof_aux, int h_fd, t_env *env)
{
	char	*line;

	while (1)
	{
		line = readline(eof_aux);
		if (line == NULL || ft_strcmp(eof + 1, line) == 0)
		{
			free(line);
			return ;
		}
		if (eof[0] == DONT_EXPAND)
			write(h_fd, line, ft_strlen(line));
		else
			write_heredoc_expanded(line, h_fd, env);
		write(h_fd, "\n", 1);
		free(line);
	}
}

char	*here_dokeitor(char *eof, char *new_temp_file, int *status, t_env *env)
{
	int		heredoc_fd;
	char	*eof_aux;
	pid_t	family;

	if (!new_temp_file)
		return (NULL);
	heredoc_fd = open(new_temp_file, O_HEREDOC, STD_PERMISSIONS);
	if (heredoc_fd == -1)
		return (unlink(new_temp_file), NULL);
	family = fork();
	if (family == CHILD)
	{
		signal(SIGINT, heredoc_signal_handler);
		eof = ft_clean_delimiter(eof);
		eof_aux = ft_strjoin(eof + 1, "->");
		while_write_heredoc(eof, eof_aux, heredoc_fd, env);
		close(heredoc_fd);
		free(eof_aux);
		free(eof);
		free(new_temp_file);
		exit(0);
	}
	*status = heredoc_father(heredoc_fd);
	return (new_temp_file);
}

int	find_heredoc(t_command *command)
{
	t_redirect	*file;
	int			status;

	status = 0;
	while (command && status != SIGINT_SIGNAL)
	{
		file = command->head_redirect;
		while (file && status != SIGINT_SIGNAL)
		{
			if (file->redirect_type == T_HERE_DOC)
			{
				file->name = here_dokeitor(file->name,
						filename_generator(), &status, command->env);
			}
			file = file->next;
		}
		command = command->next;
	}
	g_exit_status = status;
	return (status);
}
