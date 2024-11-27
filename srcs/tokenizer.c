#include "minishell.h"

t_token	*symbol_tokenizer(e_token_value type, char *line, int n_symbol)
{
	int		i;

	i = 0;
	if (line[i + n_symbol] != '\0' && line[i + n_symbol] <= ' ')
		i++;
	while (line[i + n_symbol] && ft_strchr(SYMBOLS, line[i + n_symbol]) == NULL)
		i++;
	return (new_token(type, line, i + n_symbol));
}

t_token	*token_chooser(char *line, t_env *env)
{
	if (line[0] == '<')
	{
		if (line[1] && line[1] == '<')
			return (new_token(T_HERE_DOC, line, 2));
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
	return (NULL);
}	

int	wordeitor(t_token **head_token, char *start_word)
{
	t_token	*fresh_token;
	int		i;

	i = 0;
	while (start_word[i] && ft_strchr("\"\'<>|$ ", start_word[i]) == NULL)
		i++;
	fresh_token = new_token(T_WORD, start_word, i);
	add_token_back(head_token, fresh_token);
	return (i);
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
		if (ft_strchr("<>|$\"\'", line[i]) != NULL)
		{	
			fresh_token = token_chooser(&line[i], env);
			if (fresh_token == NULL)
				freedom_error_fresh_token(head_token, line, env);
			add_token_back(&head_token, fresh_token);
			i += fresh_token->length;
		}
		else if (line[i] <= ' ')
			i++;
		else
			i += wordeitor(&head_token, &line[i]);
	}
	return (head_token);
}
