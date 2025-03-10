/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoteitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:25:01 by psapio            #+#    #+#             */
/*   Updated: 2025/03/03 20:00:13 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_is_dollar(char **expanded, char *after_dollar, int *i, t_env *env)
{
	char	*aux;
	int		n;

	n = 1;
	if (after_dollar[n] == '?')
	{
		*expanded = ft_itoa(g_exit_status);
		(*i)++;
	}
	else if (after_dollar[n] == '$')
	{
		aux = get_pid_quote();
		*expanded = ft_strjoin(*expanded, aux);
		free(aux);
		(*i)++;
	}
	else if (!(ft_isalnum(after_dollar[n]) == 1 || after_dollar[n] == '_'))
		*expanded = ft_strjoin(*expanded, "$");
	else if ((ft_isalnum(after_dollar[n]) == 1 || after_dollar[n] == '_'))
	{
		*expanded = ft_strjoin(*expanded,
				maybe_expanded(i, &after_dollar[n], env));
	}
}

void	if_not_dollar(char **expanded, char *start_quote, int *i)
{
	char	*aux;

	aux = *expanded;
	if (start_quote[0] != ' ')
	{
		aux = nothing_to_expand(i, start_quote);
		*expanded = ft_strjoin(*expanded, aux);
		free(aux);
	}
	else
		*expanded = ft_strjoin(*expanded, " ");
}

void	check_if_dollar(char **expanded, char *start_quote, int *i, t_env *env)
{
	if (*(start_quote + *i) == '$')
		if_is_dollar(expanded, start_quote + *i, i, env);
	else
		if_not_dollar(expanded, start_quote + *i, i);
}

t_token	*expand_d_quote(char *start_quote, int length_dq, t_env *env)
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
		check_if_dollar(&expanded, start_quote, &i, env);
		if (aux)
		{
			free(aux);
			aux = NULL;
		}
		i++;
		if (start_quote[i] == '\"')
			break ;
	}
	token_d_quote = new_token(T_D_QUOTE, start_quote, length_dq);
	token_d_quote->expanded = expanded;
	token_d_quote->free_expanded = true;
	return (token_d_quote);
}
