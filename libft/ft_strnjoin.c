/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:28:45 by anfi              #+#    #+#             */
/*   Updated: 2024/10/11 22:32:07 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, int n)
{
	size_t			len_s1;
	size_t			len_s2;
	unsigned int	i;
	unsigned int	j;
	char			*s3;

	if (!s1 && !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = -1;
	j = 0;
	s3 = ft_calloc((len_s1 + len_s2 + 1), sizeof(char));
	if (!s3)
		return (0);
	while (j <= n && ++i < len_s1)
		s3[j++] = s1[i];
	i = -1;
	while (j <= n && ++i < len_s2)
		s3[j++] = s2[i];
	return (s3);
}
