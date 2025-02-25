#include "minishell.h"

t_token	*symbol_tokenizer(e_token_value type, char *line, int n_symbol)
{
	int		i;

	i = 0;
	if (line[i + n_symbol] != '\0' &&  ft_strchr(SPACES, line[i + n_symbol]))
		i++;
	while (line[i + n_symbol] && ft_strchr(SYMBOLS, line[i + n_symbol]) == NULL)
		i++;
	return (new_token(type, line, i + n_symbol));
}
t_token	*token_chooser2_space_version(char *line)
{
	int i;
	
	i = 0;
	while (line[i] && ft_strchr(SPACES, line[i]))
		i++;
	return (new_token(T_SPACE, line, i));
}

t_token	*token_chooser(char *line, t_env *env)
{
	if (line[0] == '<')
	{
		if (line[1] && line[1] == '<')
			return (new_token(T_HERE_DOC, line, 2));
		else if (line[1] && line[1] == '>')
			return (new_token(T_IN_OUT, line, 2));
		return (new_token(T_REDIRECT_LEFT, line, 1));
	}
	if (line[0] == '>')
	{
		if (line[1] && line[1] == '>')
			return (new_token(T_APPEND, line, 2));
		return (new_token(T_REDIRECT_RIGHT, line, 1));
	}
	if (line[0] == '|')
		return (new_token(T_PIPE, line, 1));
	if (line[0] == '$')
	{
		if (line[1] && line[1] == '$')
			return (get_pid_expandetor());
		return (expandetor(line, env));
	}
	if (line[0] == '\'' || line[0] == '\"')
		return (create_str_quote(line, env));
	return (token_chooser2_space_version(line));
}

int	wordeitor(t_token **head_token, char *start_word)
{
	t_token	*fresh_token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (start_word[i] && ft_strchr(SPACES, start_word[i]))
		i++;
	while (start_word[i + j] && ft_strchr("\"\'<>|$ ", start_word[i + j]) == NULL)
		j++;
	if (j == 0)
		return (i);
	fresh_token = new_token(T_WORD, start_word, i + j);
	add_token_back(head_token, fresh_token);
	return (i + j);
}

t_token	*create_space_token(char *line, int *n)
{
	int	i;
	t_token *token;

	i = 0;
	while (line[i] && ft_strchr(SPACES, line[i]))
		i++;
	token = new_token(T_SPACE, line, i);
	n += i;
	return (token);
}

int	find_valid_delimitor(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(SPACES""SYMBOLS, line[i]) != NULL)
			break;
		if (ft_strchr(QUOTES, line[i]) != NULL)
		{
			quote = line[i];
			i++;
			while (line[i] != quote)
				i++;
		}
		i++;
	}
	return (i);
}

t_token	*handle_heredoc_limiter(char *line, t_env *env)
{
	t_token		*new;
	char		*delimiter;
	char		*aux;
	int			i;

	i = 0;
	while (line[i] && ft_strchr(SPACES, line[i]) != NULL)
		i++;
	i += find_valid_delimitor(&line[i]);
	if (i == 0)
		return (token_chooser(line, env));
	delimiter = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(delimiter, line, i + 1);
	aux = ft_strtrim(delimiter, SPACES);
	free(delimiter);
	delimiter = ft_strchrtrim(aux, '\"');
	new = new_token(T_WORD, line, i);
	new->expanded = delimiter;
	new->free_expanded = true;
	return (new);
}

t_token	*tokenizer(char *line, t_env *env)
{
	t_token	*fresh_token;
	t_token	*head_token;
	int		i;

	i = 0;
	head_token = NULL;
	while (line[i])
	{
		if (ft_strchr("<>|$\"\'"SPACES, line[i]) != NULL)
		{
			if (fresh_token && fresh_token->type == T_HERE_DOC)
				fresh_token = handle_heredoc_limiter(&line[i], env);
			else
				fresh_token = token_chooser(&line[i], env);

			if (fresh_token == NULL)
				freedom_error_fresh_token(head_token, line, env);
			add_token_back(&head_token, fresh_token);
			i += fresh_token->length;
		}
		else
			i += wordeitor(&head_token, &line[i]);
	}
	return (head_token);
}
