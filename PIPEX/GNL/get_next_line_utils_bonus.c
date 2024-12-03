/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:18:11 by psapio            #+#    #+#             */
/*   Updated: 2024/01/19 19:46:58 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(const char *s1)
{
	size_t	size_p;
	char	*s1double;
	size_t	i;

	i = 0;
	size_p = ft_strlen(s1);
	s1double = malloc(size_p + 1);
	if (s1double == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s1double[i] = s1[i];
		i++;
	}
	s1double[i] = '\0';
	return (s1double);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	character;

	character = (char)c;
	i = 0;
	if (character == '\0')
	{
		while (s[i] != '\0')
		{
			i++;
		}
		return ((char *)&s[i]);
	}
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	ii;
	size_t	longstr;
	char	*string3;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	longstr = ft_strlen(s1) + ft_strlen(s2);
	string3 = malloc(longstr + 1);
	if (string3 == NULL)
		return (NULL);
	string3[longstr] = '\0';
	while (s1[i] != '\0')
	{
		string3[i] = s1[i];
		i++;
	}
	ii = 0;
	while (s2[ii] != '\0')
		string3[i++] = s2[ii++];
	string3[i] = '\0';
	return (string3);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	substring_length;
	size_t	i;
	size_t	input_length;
	char	*substring;

	if (s == NULL)
		return (NULL);
	input_length = ft_strlen(s);
	if (start >= input_length)
		return (ft_strdup(""));
	if (input_length - start < len)
		substring_length = input_length - start;
	else
		substring_length = len;
	substring = (char *)malloc(substring_length + 1);
	if (substring == NULL)
		return (NULL);
	i = 0;
	while (i < substring_length)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
