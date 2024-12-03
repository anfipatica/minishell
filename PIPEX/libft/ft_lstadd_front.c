/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:52:22 by psapio            #+#    #+#             */
/*   Updated: 2024/07/01 19:10:15 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL || lst == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

//lst[0][0] es el siguente nodo?
/*
int main(void)
{
	t_list *lista;
	t_list *nodo;
	char content1[] = "Paolo";
	char content2[] = "Javi";

	lista = ft_lstnew(content1);
	nodo = ft_lstnew(content2);

	ft_lstadd_front(&lista, nodo);
	printf("valor en primer nodo (lista): %s\n", lista->content);//javi
	printf("valor en segundo nodo (lista): %s\n", (lista->next)->content);
}
*/
/*
int main(void)
{
	int numeros[3] = { 8 , 6 , 4  };

	t_list *nodo1;
	t_list *nodo2;
	t_list *nodo3;
	t_list *iter;

	nodo1 = ft_lstnew(&numeros[0]); //aqui ponenos el 8
	nodo2 = ft_lstnew(&numeros[1]); //aqui ponemos el 6
	nodo3 = ft_lstnew(&numeros[2]); //aqui ponemos el 4
	nodo1->next = nodo2; //nodo1->content tenemos 8 y 
(esto entre parentesis es nodo2)(nodo1->next)->content 6
	ft_lstadd_front(&nodo1, nodo3);

	iter = nodo1;

	while (iter != NULL)
	{
		printf("contenido de los  nodos ∆: %d\n", ((int*)iter->content)[0]);
		iter = iter->next;
	}
}
*/
