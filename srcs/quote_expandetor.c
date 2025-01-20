#include "minishell.h"

char	*nothing_to_expand(int *n, char *str)
{
	int		i;
	char	*literal;

	i = 0;
	dprintf(2, "ENNE N: %d string: %s\n", *n, str);
	while (str[i] != '\"' && str[i] != '$' && str[i] != ' ')
	{
		i++;
	}
	*n += i - 1;
	literal = ft_substr(str, 0, i);
	return (literal);
}

char	*maybe_expanded(int *n, char *str, t_env *env)
{
	int	i;

	char *maybe_expanded_str;
	i = 0;

	while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	*n += i;
	dprintf(2, "enVv: %*s\n", i, str);
	maybe_expanded_str = ft_getenv(str, env, i);
	dprintf(2, "in maybe_expanded: str = %s\n", maybe_expanded_str);
	return (maybe_expanded_str);
}

char	*get_pid_quote(void)
{
	int		fd;
	int		read_return;
	char	temp[15];
	char	*pid;

	ft_memset(&temp, 0, 15);
	fd = open("/proc/self/stat", O_RDONLY); //abre un archivo donde está información del proceso actual.
	read_return = read(fd, temp, 14);
	(void)read_return;
	pid = ft_substr(temp, 0, ft_strchr(temp, ' ') - temp);
	close(fd);
	return (pid);
}


