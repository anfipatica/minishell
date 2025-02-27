/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:16 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/28 00:09:34 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env *env)
{
	char	*path;

	path = ft_getenv("PATH", env, 0);
	if (path)
	{
		printf("%s\n", path);
		free(path);
	}
	else
		write(2, "path not found\n", 16);
}
