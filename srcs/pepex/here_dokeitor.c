/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dokeitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:52:31 by psapio            #+#    #+#             */
/*   Updated: 2025/02/27 13:26:23 by psapio           ###   ########.fr       */
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

int	heredoc_father(int heredoc_fd)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	wait(&status);
	close(heredoc_fd);
	return (WEXITSTATUS(status));
}

//	delimiter = ft_strchrtrim(aux, '\"');

bool	ft_ultrastrchr(char	*str, char	*find)
{
	int	i;

	i = -1;
	while (find[++i])
	{
		if (ft_strchr(str, find[i]))
			return (true);
	}
	return (false);
}

//'"a" '''a''' "hola'"'"
//"a" a "hola'
#define dont_expand '0'
#define expand '1'
char	*ft_clean_delimiter(char *delimiter)
{
	int		i;
	int		j;
	char	quote;
	char	*clean_delimiter;
	
	i = 0;
	j = 1;
	clean_delimiter = ft_calloc(ft_strlen(delimiter), sizeof(char) + 2);
	while (delimiter[i])
	{
		if (ft_strchr(QUOTES, delimiter[i]))
		{
			quote = delimiter[i];
			while (delimiter[++i] && delimiter[i] != quote)
				clean_delimiter[j++] = delimiter[i];
			i++;
		}
		else
			clean_delimiter[j++] = delimiter[i++];
	}
	if (i == (j - 1))
		clean_delimiter[0] = expand;
	else
		clean_delimiter[0] = dont_expand;
	return (clean_delimiter);
}

void	write_heredoc_expanded(char *delimiter, char *line, int heredoc_fd, t_env *env)
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
bool	write_heredoc(char *delimiter, char *line, int heredoc_fd, t_env *env)
{
	if (line == NULL || ft_strcmp(delimiter + 1, line) == 0)
	{
		free(line);
		return (false);
	}
	if (delimiter[0] == dont_expand)
		write(heredoc_fd, line, ft_strlen(line));
	else
		write_heredoc_expanded(delimiter, line, heredoc_fd, env);
	write(heredoc_fd, "\n", 1);
	free(line);
	return (true);
}

char	*here_dokeitor(char *delimiter, char *new_temp_file, int *status, t_env *env)
{
	int		heredoc_fd;
	char	*input_line;
	char	*delimiter_aux;
	pid_t	family;

	if (!new_temp_file)
		return (NULL);
	printf("new_temp_file: %s\n", new_temp_file);
	heredoc_fd = open(new_temp_file, O_WRONLY | O_CREAT | O_TRUNC, STD_PERMISSIONS);
	printf("heredoc_fd: %d\n", heredoc_fd);
	if (heredoc_fd == -1)
		return (unlink(new_temp_file), NULL);

	family = fork();
	if (family == CHILD)
	{
		signal(SIGINT, heredoc_signal_handler);
		delimiter = ft_clean_delimiter(delimiter);
		delimiter_aux = ft_strjoin(delimiter + 1, "->");
		while (1)
		{
			input_line = readline(delimiter_aux);
			if (write_heredoc(delimiter, input_line, heredoc_fd, env) == false)
				break;
		}
		close(heredoc_fd);
		free(delimiter_aux);
		free(delimiter);
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
				file->name = here_dokeitor(file->name, filename_generator(), &status, command->env);
			file = file->next;
		}
		command = command->next;
	}
	g_exit_status = status;
	return (status);
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