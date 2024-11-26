
#include "minishell.h"

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
