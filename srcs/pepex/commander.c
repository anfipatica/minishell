/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:13:14 by psapio            #+#    #+#             */
/*   Updated: 2025/01/09 16:07:28 by ymunoz-m         ###   ########.fr       */
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
		exit(1);
	}
}

char	*find_path_name(char *cmd, t_env *env, char **cmd_arg)
{
	char	**all_path;
	char	*path_name;
	int		i;
	if (cmd == NULL || ft_strchr(cmd, '/') != NULL)
		return (cmd);
	i = 0;
	while (env != NULL)
	{
		if (ft_strncmp(env->name, "PATH", 4) == 0)
		{
			all_path = ft_split(env->value, ':');
			if (all_path == NULL)
				return (NULL);
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
		return (NULL);
	path_name = check_path(all_path, cmd);
	error_path(path_name, cmd, all_path, cmd_arg);
	free_double_pointer(all_path);
	return (path_name);
}
