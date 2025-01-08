/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:31:25 by jvasquez          #+#    #+#             */
/*   Updated: 2025/01/07 14:35:08 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Esta función *recursiva* soluciona el problema de eliminar nodos en listas
  unidireccionales. Se encarga de reenlazar la lista correctamente.*/
t_list *eval(t_list *lst, void *context, bool (*predicate)(void *, void *), void (*del)(void *))
{
	t_list *result = NULL;

	if (!lst)
		return NULL;
	lst->next = eval(lst->next, context, predicate, del);
	printf("predicate devuelve: %d\n", predicate(lst->content, context));
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
