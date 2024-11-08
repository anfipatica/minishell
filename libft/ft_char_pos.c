/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:32:28 by anfi              #+#    #+#             */
/*   Updated: 2024/10/15 19:14:53 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * This function searchs for c char inside str. If found, it returns
 * the possition right before it's location inside str.
 * Else, it will return the last position of str.
 */
int	ft_char_pos(char c, char *str)
{
	int	i;

	i = -1;
	if (str[0] == c)
		return (0);
	while (str[++i])
	{
		if (str[i] == c)
			break;
	}
	return (i - 1);
}