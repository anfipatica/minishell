/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:45:54 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/27 19:03:25 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	matrix_filler(t_command *command, char ***matrix)
{
	matrix[ARGS] = lts_args_to_matrix(command->args);
	matrix[ENV] = lts_env_to_matrix(command->env);
	if (matrix[ARGS] == NULL)
		exit(0);
}

void	restore_builtin_fds(int aux_stdout, int aux_stdin)
{
	dup2(aux_stdout, 1);
	close(aux_stdout);
	dup2(aux_stdin, 0);
	close(aux_stdin);
}

void	restore_daddy_fds(bool multiple_commands, int in_fd, int *pipefd)
{
	if (multiple_commands == true)
	{
		close(in_fd);
		in_fd = pipefd[IN_FILE];
		close(pipefd[OUT_FILE]);
	}
}
