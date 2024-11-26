
#include "minishell.h"

char *next_to_dollar(char *expanded, char *line_after_dollar, int *i, t_env *env)
{
	char	*aux;
	int n;
	
	n = 1;
	if (line_after_dollar[n] == ' ' || line_after_dollar[n] == '\"')
		expanded = ft_strjoin(expanded, "$");
	else if ((ft_isalpha(line_after_dollar[n]) == 1 || line_after_dollar[n] == '_'))
		expanded = ft_strjoin(expanded, maybe_expanded(i, &line_after_dollar[n], env));
	else if (line_after_dollar[n] == '$')
	{
		aux = get_pid_quote();
		expanded = ft_strjoin(expanded, aux);
		free(aux);
		(*i)++;
	}
	return (expanded);
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
			expanded = next_to_dollar(expanded, &start_quote[i], &i, env);
			printf("---expanded = %s\n", expanded);
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
