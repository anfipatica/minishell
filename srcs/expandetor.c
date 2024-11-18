#include "minishell.h"

t_token	*expandetor(char *line)
{
//	printf("string orniginal llegado = %s\n", str);
	int		i;
	t_token	*token;

	if (ft_isdigit(line[1]) == 1)
		return (new_token(T_ENV, line, 1));
	if (ft_isalpha(line[1]) == 0 && line[1] != '_')
		return (new_token(T_ENV, line, 1));
	i = 1;
	while (line[i] && ft_isalnum(line[i]) == 1)
	{
		i++;
		printf("%d\n", i);
	}
	token = new_token(T_ENV, line, i);
	token->expanded = getenv((token->str) + 1); //getenv no hace malloc, no hay que liberar!!!!
	printf("token->str + 1 = %s\n", (token->str) + 1);
	return (token);
}

t_token	*get_pid_expandetor(void)
{
	int		fd;
	char	*temp;
	t_token	*token;

	fd = open("/proc/self/stat", O_RDONLY); //abre un archivo donde está información del proceso actual.
	temp = ft_calloc(50, sizeof(char));
	if (!temp)
		return (NULL);
	read(fd, temp, 49);
	printf("temp = %s\n", temp);
	token = new_token(T_ENV, "$$", 2);
	token->expanded = ft_substr(ft_strchr(temp, 'R'), 2, 6);
	token->free_expanded = true;
	free(temp);
	return (token);
}


