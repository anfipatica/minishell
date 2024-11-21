#include "minishell.h"

// char	*expandetor(char *line, t_env *env)
// {
// 	int		i;

// 	if (ft_isdigit(line[1]) == 1)
// 		return (new_token(T_ENV, line, 1));
// 	if (ft_isalpha(line[1]) == 0 && line[1] != '_')
// 		return (new_token(T_ENV, line, 1));
// 	i = 1;
// 	while (line[i] && (ft_isalnum(line[i]) == 1) || line[i] == '_')
// 		i++;
// 	ft_getenv((token->str) + 1, env)
// }

//t_token	*make_t_env_token(char *line, t_env *env)
t_token	*expandetor(char *line, t_env *env)
{
	int		i;
	t_token	*token;

	//expandetor(line, env);
	if (ft_isdigit(line[1]) == 1)
		return (new_token(T_ENV, line, 1));
	if (ft_isalpha(line[1]) == 0 && line[1] != '_')
		return (new_token(T_ENV, line, 1));
	i = 1;
	while (line[i] && (ft_isalnum(line[i]) == 1 || line[i] == '_'))
		i++;
	token = new_token(T_ENV, line, i);
	token->expanded = ft_getenv((token->str) + 1, env, 0); //getenv no hace malloc, no hay que liberar!!!!
	return (token);
}

/**
 * This function emulates getpid(), returning a token with the
 * pid in case the prompt finds "$$"
 */
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


