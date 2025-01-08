
#include "minishell.h"

void if_is_dollar(char **expanded, char *line_after_dollar, int *i, t_list *env)
{
	char	*aux;
	int n;
	
	n = 1;
	if (line_after_dollar[n] == '$')
	{
		aux = get_pid_quote();
		*expanded = ft_strjoin(*expanded, aux);
		free(aux);
		(*i)++;
	}
	// TODO si despues del dollar tenemos ? eentonces expandir con el valor de la ultima saldia de programa
	else if (!(ft_isalpha(line_after_dollar[n]) == 1 || line_after_dollar[n] == '_'))
		*expanded = ft_strjoin(*expanded, "$");
	else if ((ft_isalpha(line_after_dollar[n]) == 1 || line_after_dollar[n] == '_'))
		*expanded = ft_strjoin(*expanded, maybe_expanded(i, &line_after_dollar[n], env));
}
void if_not_dollar(char **expanded, char *start_quote, int *i)
{
	char	*aux;

	aux = NULL;
	if (start_quote[0] != ' ')
	{
		aux = nothing_to_expand(i, start_quote);
		printf("aux = %s\n", aux);
		*expanded = ft_strjoin(*expanded, aux);
		printf("expanded = %s\n", *expanded);
		free(aux);
	}
	else
		*expanded = ft_strjoin(*expanded, " ");
}
t_token *expand_d_quote(char *start_quote, int length_dq, t_list *env)
{
	char	*expanded;
	char	*aux;
	t_token	*token_d_quote;
	int		i;

	i = 1;
	expanded = NULL;

	while (1)
	{
		aux = expanded;
		if (start_quote[i] == '$')
			if_is_dollar(&expanded, &start_quote[i], &i, env);
		else
			if_not_dollar(&expanded, &start_quote[i], &i);
		if (aux)
		{
			free(aux);
			aux = NULL;
		}
		// printf("I: %i\n", i);
		// printf("str: %s\n", start_quote + i);
		i++;
		if (start_quote[i] == '\"')
			break ;
	
	}
	token_d_quote = new_token(T_D_QUOTE, start_quote, length_dq);
	token_d_quote->expanded = expanded;
	token_d_quote->free_expanded = true;
	printf("token_d_quote: %s\n", token_d_quote->expanded);
	return (token_d_quote);
}
