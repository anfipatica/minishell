/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promptereitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:19:24 by psapio            #+#    #+#             */
/*   Updated: 2025/02/28 18:41:12 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	twin_quote(char *line)
{
	int		i;
	char	quote_type;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote_type = line[i];
			i++;
			while (line[i] != '\0' && line[i] != quote_type)
				i++;
		}
		if (line[i] == '\0')
		{
			write(2, RED"Hey,\n"
				"your quote is missing a buddy to complete the pair!\n"
				"Don’t leave it hanging, it’s lonely!\n"STD, 109);
			free(line);
			return (false);
		}
		i++;
	}
	return (true);
}

int	promptereitor(t_env *env)
{
	char		*line;
	t_token		*first_token;
	t_command	*command;

	while (true)
	{
		signal(SIGINT, father_signal_handler);
		line = readline("prompt > ");
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			if (twin_quote(line) == false)
				continue ;
			first_token = tokenizer(line, env);
			list_checker(&first_token);
			command = automata(first_token, env);
			begin_execution(command);
			ft_free_commands(command);
			ft_free_tokens(first_token);
		}
		free(line);
	}
	return (free(line), rl_clear_history(), 0);
}
