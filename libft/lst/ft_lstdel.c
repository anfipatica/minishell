/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:31:25 by jvasquez          #+#    #+#             */
/*   Updated: 2024/12/18 19:28:06 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *eval(t_list *lst, void *context, bool (*predicate)(void *, void *), void (*del)(void *))
{
	t_list *result = NULL;

	if (!lst)
		return NULL;

	lst->next = eval(lst->next, context, predicate, del);

	if (predicate(lst->content, context))
	{
		result = lst->next;
		ft_lstdelone(lst, del);
	}
	else
		result = lst;
	return result;
	
}


void	ft_lstdel(t_list **lst, void *context, bool (*predicate)(void *, void *), void (*del)(void *))
{
	*lst = eval(*lst, context, predicate, del);
}
