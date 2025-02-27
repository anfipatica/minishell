/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:36:56 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/27 20:41:19 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_valid_delimitor(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(SPACES""SYMBOLS, line[i]) != NULL)
			break ;
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
	delimiter = NULL;
	while (line[i] && ft_strchr(SPACES, line[i]) != NULL)
		i++;
	i += find_valid_delimitor(&line[i]);
	if (i == 0)
		return (token_chooser(line, env));
	aux = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(aux, line, i + 1);
	delimiter = ft_strtrim(aux, SPACES);
	free(aux);
	new = new_token(T_WORD, line, i);
	new->expanded = delimiter;
	new->free_expanded = true;
	return (new);
}
