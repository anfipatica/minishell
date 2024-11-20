#include "minishell.h"

t_token	*expandetor(char *line)
{
	int		i;
	t_token	*token;

	if (ft_isdigit(line[1]) == 1)
		return (new_token(T_ENV, line, 1));
	if (ft_isalpha(line[1]) == 0 && line[1] != '_')
		return (new_token(T_ENV, line, 1));
	i = 1;
	while (line[i] && ft_isalnum(line[i]) == 1)
		i++;
	token = new_token(T_ENV, line, i);
	token->expanded = getenv((token->str) + 1); //getenv no hace malloc, no hay que liberar!!!!
	return (token);
}

t_token	*get_pid_expandetor(void)
{
	int		fd;
	char	temp[15];
	t_token	*token;

	ft_memset(&temp, 0, 15);
	fd = open("/proc/self/stat", O_RDONLY); //abre un archivo donde está información del proceso actual.
	read(fd, temp, 14);
	token = new_token(T_ENV, "$$", 2);
	token->expanded = ft_substr(temp, 0, ft_strchr(temp, ' ') - temp);
	token->free_expanded = true;
	return (token);
}


