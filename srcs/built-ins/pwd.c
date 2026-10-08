/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:16 by ymunoz-m          #+#    #+#             */
/*   Updated: 2026/10/08 11:10:21 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env *env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		printf("%s\n", path);
		free(path);
	}
	else
	{
		path = ft_getenv("PWD", env, 0);
		if (!path)
			write(2, "PWD not found\n", 14);
		else
			printf("%s\n", path);
	}
}
