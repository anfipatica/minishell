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
t_token	*token_chooser2_space_version(char *line)
{
	int i;
	
	i = 0;
	while (line[i] && line[i] <= ' ')
		i++;
	printf("i = %d\n", i);
	return (new_token(T_SPACE, line, i));
}

t_token	*token_chooser(char *line, t_list *env)
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

int	wordeitor(t_list **head_token, char *start_word)
{
	t_token	*fresh_token;
	t_list	*list_token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (start_word[i] && start_word[i] <= ' ')
		i++;
	while (start_word[i + j] && ft_strchr("\"\'<>|$ ", start_word[i + j]) == NULL)
		j++;
	if (j == 0)
		return (i);
	fresh_token = new_token(T_WORD, start_word, i + j);
	list_token = ft_lstnew(fresh_token);
	ft_lstadd_back(head_token, list_token);
	return (i + j);
}

t_token	*create_space_token(char *line, int *n)
{
	int	i;
	t_token *token;

	i = 0;
	while (line[i] && line[i] <= ' ')
		i++;
	token = new_token(T_SPACE, line, i);
	n += i;
	return (token);
}

t_list	*tokenizer(char *line, t_list *list_env)
{
	t_token	*fresh_token;
	t_list	*list_token;
	t_list	*head_list_token;
	int		i;

	i = 0;
	head_list_token = NULL;
	while (line[i])
	{
		if (ft_strchr("<>|$\"\' ", line[i]) != NULL)
		{	
			fresh_token = token_chooser(&line[i], list_env);
			if (fresh_token == NULL)
				freedom_error_fresh_token(head_list_token, line, list_env);
			i += fresh_token->length;
			list_token = ft_lstnew(fresh_token);
			ft_lstadd_back(&head_list_token, list_token);
		}
		else
			i += wordeitor(&head_list_token, &line[i]);
	}
	return (head_list_token);
}
