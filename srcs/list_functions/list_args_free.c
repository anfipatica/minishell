/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_args_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:05:37 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/27 20:15:32 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_one_args(t_args *args)
{
	if (!args)
		return ;
	free(args);
}

void	ft_free_list_args(t_args *arg_node)
{
	t_args	*temp;

	if (!arg_node)
	{
		return ;
	}
	while (arg_node)
	{
		temp = arg_node->next;
		ft_free_one_args(arg_node);
		arg_node = temp;
	}
}
