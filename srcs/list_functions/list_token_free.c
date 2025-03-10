/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:05:37 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/03/03 17:14:07 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*check_and_delete_space(t_token *lst)
{
	t_token	*result;

	result = NULL;
	if (!lst)
		return (NULL);
	lst->next = check_and_delete_space(lst->next);
	if (lst->type == T_SPACE)
	{
		result = lst->next;
		ft_free_one_node(lst);
	}
	else
		result = lst;
	return (result);
}

t_token	*check_and_delete_env(t_token *lst, t_token *lst_prev)
{
	t_token	*result;

	result = NULL;
	if (!lst_prev && (lst->type == T_ENV && !(lst->expanded)))
		return (ft_free_one_node(lst), check_and_delete_env(lst->next, lst));
	if (!lst)
		return (NULL);
	lst->next = check_and_delete_env(lst->next, lst);
	if (lst->type == T_WORD && lst_prev && lst_prev->type == T_HERE_DOC)
	{
		lst->str = ft_strchrtrim(lst->str, '\"');
		result = lst;
	}
	else if (lst->type == T_ENV
		&& !(lst->expanded) && (lst_prev) && lst_prev->type != T_HERE_DOC)
	{
		result = lst->next;
		ft_free_one_node(lst);
	}
	else
		result = lst;
	return (result);
}
