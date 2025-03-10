/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:41:30 by psapio            #+#    #+#             */
/*   Updated: 2025/03/04 13:24:06 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*symbol_tokenizer(t_token_value type, char *line, int n_symbol)
{
	int	i;

	i = 0;
	if (line[i + n_symbol] != '\0' && ft_strchr(SPACES, line[i + n_symbol]))
		i++;
	while (line[i + n_symbol] && ft_strchr(SYMBOLS, line[i + n_symbol]) == NULL)
		i++;
	return (new_token(type, line, i + n_symbol));
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
	while (start_word[i + j]
		&& ft_strchr(SPACES""QUOTES""SYMBOLS"$", start_word[i + j]) == NULL)
		j++;
	if (j == 0)
		return (i);
	fresh_token = new_token(T_WORD, start_word, i + j);
	add_token_back(head_token, fresh_token);
	return (i + j);
}

t_token	*create_space_token(char *line, int *n)
{
	int		i;
	t_token	*token;

	i = 0;
	while (line[i] && ft_strchr(SPACES, line[i]))
		i++;
	token = new_token(T_SPACE, line, i);
	n += i;
	return (token);
}

t_token	*tokenizer(char *line, t_env *env)
{
	t_token	*fresh_token;
	t_token	*head_token;
	int		i;

	i = 0;
	head_token = NULL;
	fresh_token = NULL;
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
