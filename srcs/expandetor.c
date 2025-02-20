
#include "minishell.h"

t_token	*expand_exit_status(char *line)
{
	t_token	*token;

	token = new_token(T_ENV, line, 2);
	token->expanded = ft_itoa(g_exit_status);
	token->free_expanded = true;
	return (token);
}

t_token	*expandetor(char *line, t_env *env)
{
	int		i;
	t_token	*token;
	if (line[1] == '?')
		return (expand_exit_status(line));
	if (ft_isdigit(line[1]) == 1)
		return (new_token(T_ENV, line, 1));
	if (ft_isalpha(line[1]) == 0 && line[1] != '_')
		return (new_token(T_ENV, line, 1));
	i = 1;
	while (line[i] && (ft_isalnum(line[i]) == 1 || line[i] == '_'))
		i++;
	token = new_token(T_ENV, line, i);
	token->expanded = ft_getenv((token->str) + 1, env, 0);
	return (token);
}

char		*get_char_pid()
{
	int		fd;
	char	temp[15];
	int read_return;

	ft_memset(&temp, 0, 15);
	fd = open("/proc/self/stat", O_RDONLY);
	read_return = read(fd, temp, 14);
	close(fd);
	if (read_return == -1)
		return (NULL);
	return (ft_substr(temp, 0, ft_strchr(temp, ' ') - temp));
}
/*
	This function emulates getpid(),
	returning a token with the
	pid in case the prompt finds "$$"
*/
t_token	*get_pid_expandetor()
{
	t_token	*token;

	token = new_token(T_ENV, "$$", 2);
	token->expanded = get_char_pid();
	token->free_expanded = true;
	return (token);
}
