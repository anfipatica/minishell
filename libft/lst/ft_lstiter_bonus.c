/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:31:25 by jvasquez          #+#    #+#             */
/*   Updated: 2024/12/18 17:30:41 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*function)(void *))
{
	t_list	*temp;

	if (!lst || !function)
		return ;
	temp = lst;
	while (temp)
	{
		function(temp->content);
		temp = temp->next;
	}
}
