/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:13:14 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/27 21:01:39 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup2_openeitor(char *file, int flags, mode_t mode, int system_fd)
{
	int	file_fd;

	file_fd = open(file, flags, mode);
	if (file_fd == -1)
	{
		perror(file);
		return (OPEN_ERROR);
	}
	if (dup2(file_fd, system_fd) == -1)
		return (perror(file), OPEN_ERROR);
	close(file_fd);
	return (file_fd);
}

int	handle_files(t_redirect *file)
{
	int	state;

	state = 0;
	while (file && state != OPEN_ERROR)
	{
		if (file->redirect_type == T_REDIRECT_RIGHT)
		{
			state = dup2_openeitor(file->name,
					O_REDIRECT_RIGHT, STD_PERMISSIONS, OUT_FILE);
		}
		else if (file->redirect_type == T_APPEND)
		{
			state = dup2_openeitor(file->name,
					O_REDIRECT_APPEND, STD_PERMISSIONS, OUT_FILE);
		}
		else if (file->redirect_type == T_HERE_DOC)
			state = dup2_openeitor(file->name, O_READ_HEREDOC, 0, IN_FILE);
		else if (file->redirect_type == T_REDIRECT_LEFT)
			state = dup2_openeitor(file->name, O_REDIRECT_LEFT, 0, IN_FILE);
		file = file->next;
	}
	return (state);
}
