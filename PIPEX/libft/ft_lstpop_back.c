/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:11:53 by psapio            #+#    #+#             */
/*   Updated: 2024/07/01 19:11:24 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop_back(t_list **lst)
{
	t_list	*last;
	t_list	*aux_list;

	last = *lst;
	aux_list = *lst;
	while (aux_list != NULL)
	{
		if (aux_list->next && aux_list->next->next == NULL)
		{
			last = aux_list->next;
			aux_list->next = NULL;
			last->next = NULL;
			return (last);
		}
		aux_list = aux_list->next;
	}
	*lst = NULL;
	return (last);
}
