/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:31:25 by jvasquez          #+#    #+#             */
/*   Updated: 2024/12/18 17:55:11 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstfind(t_list *lst, void *context, bool (*predicate)(void *content, void *context))
{
	t_list	*temp;

	if (!lst || !predicate)
		return NULL;
	temp = lst;
	while (temp)
	{
		if(predicate(temp->content, context))
			return (temp);
		temp = temp->next;
	}
	return NULL;
}
