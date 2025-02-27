/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:15:26 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/27 19:16:00 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_command *command)
{
	if (command->execve_matrix && *(command->execve_matrix))
	{
		free(command->execve_matrix[ARGS]);
		free_double_pointer(command->execve_matrix[ENV]);
	}
	ft_free_env(command->env);
	ft_free_tokens(command->token_pointer);
	ft_free_commands(command);
}

void	freedom_error_fresh_token(t_token *head_token, char *line, t_env *env)
{
	free(line);
	ft_free_tokens(head_token);
	ft_free_env(env);
	exit(13);
}

void	free_exit_execution(char *path_name, char **matrix[2])
{
	free(path_name);
	free(matrix[ARGS]);
	free_double_pointer(matrix[ENV]);
	exit(99);
}
