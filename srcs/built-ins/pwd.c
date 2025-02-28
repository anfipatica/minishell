/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:16 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/28 19:13:30 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env *env)
{
	char	*path;

	path = ft_getenv("PWD", env, 0);
	if (path)
	{
		printf("%s\n", path);
	}
	else
		write(2, "PWD not found\n", 16);
}
