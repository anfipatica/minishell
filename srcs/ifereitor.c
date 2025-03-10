/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifereitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:33:46 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/03/03 19:56:35 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_chooser2_space_n_quote_version(char *line, t_env *env)
{
	int	i;

	i = 0;
	if (line[0] == '\'' || line[0] == '\"')
		return (create_str_quote(line, env));
	while (line[i] && ft_strchr(SPACES, line[i]))
	{
		i++;
	}
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
		if (line[1] && ft_strchr(SPACES, line[1]))
			return (new_token(T_WORD, "$", 1));
		return (expandetor(line, env));
	}
	return (token_chooser2_space_n_quote_version(line, env));
}
