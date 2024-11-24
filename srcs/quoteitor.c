#include "minishell.h"

char *nothing_to_expand(int *n, char *str)
{
	int		i;
	char	*literal;

	i = 0;
	while (str[i] != '\"' && str[i] != '$' && str[i] != ' ')
	{
		i++;
	}
	*n += i - 1;
	literal = ft_substr(str, 0, i);
	return (literal);
}

char *maybe_expanded(int *n, char *str, t_env *env)
{
	int	i;

	char *maybe_expanded_str;
	i = 0;

	while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	*n += i;
	maybe_expanded_str = ft_getenv(str, env, i);
	printf("in maybe_expanded: str = %s\n", maybe_expanded_str);
	return (maybe_expanded_str);
}

char	*get_pid_quote(void)
{
	int		fd;
	int		read_return;
	char	temp[15];
	char	*pid;
	char	*aux;

	fd = open("/proc/self/stat", O_RDONLY); //abre un archivo donde está información del proceso actual.
	read_return = read(fd, temp, 14);
	(void)read_return;
	pid = ft_substr(temp, 0, ft_strchr(temp, ' ') - temp);
	close(fd);
	return (pid);
}

t_token *expand_d_quote(char *start_quote, int length_dq, t_env *env)
{
	char	*expanded;
	char	*aux;
	char	*aux2;
	t_token	*token_d_quote;
	int		i;

	i = 1;
	expanded = NULL;
	if(start_quote[i] == '\"')
	{
		token_d_quote = new_token(T_D_QUOTE, start_quote, length_dq);
		return (token_d_quote);
	}

	while (start_quote[i] != '\"')
	{
		aux = expanded;
		if (start_quote[i] == '$')
		{
			if (start_quote[i + 1] == ' ')
				expanded = ft_strjoin(expanded, "$");
			else if (start_quote[i + 1] == '\"')
				expanded = ft_strjoin(expanded, "$");
			else if ((ft_isalpha(start_quote[i + 1]) == 1 || start_quote[i + 1] == '_'))
				expanded = ft_strjoin(expanded, maybe_expanded(&i, &start_quote[i + 1], env));
			else if (start_quote[i + 1] == '$') // ok
			{
				aux2 = get_pid_quote();
				expanded = ft_strjoin(expanded, aux2);
				free(aux2);
				i++;
			}
		}
		else
		{
			if (start_quote[i] != '$' && start_quote[i] != ' ')
			{
				aux2 = nothing_to_expand(&i, &start_quote[i]);
				expanded = ft_strjoin(expanded, aux2);
				free(aux2);
			}
			if (start_quote[i] != '$' && start_quote[i] == ' ')
				expanded = ft_strjoin(expanded, " ");
		}
		free(aux);
		i++;
	}
	token_d_quote = new_token(T_D_QUOTE, start_quote, length_dq);
	token_d_quote->expanded = expanded;
	token_d_quote->free_expanded = true;
	printf("token_d_quote: %s\n", token_d_quote->expanded);
	return (token_d_quote);
}

t_token *create_str_quote(char *start_quote, t_env *env)
{
	char	*finish_quote;
	int		length;
	finish_quote = ft_strchr(start_quote + 1, start_quote[0]);
	if (!finish_quote)
		return (NULL);
	length = ((finish_quote + 1) - start_quote);
	if (start_quote[0] == '\"')
		return (expand_d_quote(start_quote, length, env));
	return (new_token(T_S_QUOTE, start_quote, length));
}

void twin_quote(char *line)
{

	int i = 0;
	char quote_type;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote_type = line[i];
			i++;
			while (line[i] != '\0' && line[i] != quote_type)
				i++;

		}
		if (line[i] == '\0')
			exit(22);
		i++;
	}
}
