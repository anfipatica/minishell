/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:58:39 by psapio            #+#    #+#             */
/*   Updated: 2024/05/23 14:08:00 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/*
#include <stdio.h>

char *proc(t_list **head)
{
	// str se declara en stack
	char str[13] = "Hola que tal";  // <---
este texto se almacenará si o si en global

	*head = ft_lstnew(str);
	printf("%s\n", (*head)->content);
	return str;
}

int main()
{
	t_list *head = NULL;


	proc(&head);
	printf("%s\n", head->content);
	return (0);
}
*/
/*
int main(void)
{
	char cosas[]="hola yago";

	printf("valor in lista nuw: %c\n", ((char*)(ft_lstnew(cosas)->content))[0]);
}
*/
