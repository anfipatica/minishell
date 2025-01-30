/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:13:14 by psapio            #+#    #+#             */
/*   Updated: 2025/01/30 17:06:09 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WRITE 1
#define READ 0

void	print_error(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

char	*check_path(char **all_path, char *cmd)
{
	char	*path_name;
	int		i;
	char	*aux_free;

	i = 0;
	while (all_path[i])
	{
		path_name = ft_strjoin(all_path[i], "/");
		if (path_name == NULL)
			return (NULL);
		aux_free = path_name;
		path_name = ft_strjoin(path_name, cmd);
		free(aux_free);
		if (path_name == NULL)
			return (NULL);
		if (access(path_name, X_OK) == -1)
		{
			i++;
			free(path_name);
		}
		else
			return (path_name);
	}
	return (NULL);
}

void	error_path(char *path_name, char *cmd, char **all_path, char **cmd_arg)
{
	if (path_name == NULL)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 21);
		if (all_path)
			free_double_pointer(all_path);
		if (cmd_arg)
			free_double_pointer(cmd_arg);
	}
}

char	*find_path_name(char *cmd, char **envp, char **cmd_arg)
{
	(void)cmd_arg;
	char	**all_path;
	char	*path_name;
	int		i;

	if (cmd == NULL || ft_strchr(cmd, '/') != NULL || cmd[0] == '\0')
		return (cmd);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			all_path = ft_split(envp[i] + 5, ':');
			if (all_path == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	path_name = check_path(all_path, cmd);
	//error_path(path_name, cmd, all_path, cmd_arg);
	free_double_pointer(all_path);
	return (path_name);
}
