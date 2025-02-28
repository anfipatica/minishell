/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:05:37 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/28 19:05:27 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_one_env(t_env *env)
{
	if (!env)
		return ;
	free(env->name);
	free(env->value);
	free(env);
}

/**
 * ft_free_env frees the nodes of a list and the neccesary content
 * inside each of them.
 */
void	ft_free_env(t_env *env)
{
	t_env	*temp;

	if (!env)
		return ;
	while (env != NULL)
	{
		temp = env->next;
		ft_free_one_env(env);
		env = temp;
	}
}
