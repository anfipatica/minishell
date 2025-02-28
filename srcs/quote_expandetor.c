/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expandetor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:23:04 by psapio            #+#    #+#             */
/*   Updated: 2025/02/28 17:51:40 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*nothing_to_expand(int *n, char *str)
{
	int		i;
	char	*literal;

	i = 0;
	printf("str = %s.c=%c\n", str, str[i]);
	while (str[i] != '\"' && str[i] != '$' && str[i] != ' ')
	{
		printf("in c=%c\n", str[i]);
		i++;
	}
	*n += i - 1;
	printf("n = %d\n", *n);
	literal = ft_substr(str, 0, i);
	return (literal);
}

char	*maybe_expanded(int *n, char *str, t_env *env)
{
	int		i;
	char	*maybe_expanded_str;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	*n += i;
	maybe_expanded_str = ft_getenv(str, env, i);
	return (maybe_expanded_str);
}

char	*get_pid_quote(void)
{
	int		fd;
	int		read_return;
	char	temp[15];
	char	*pid;

	ft_memset(&temp, 0, 15);
	fd = open("/proc/self/stat", O_RDONLY);
	read_return = read(fd, temp, 14);
	(void)read_return;
	pid = ft_substr(temp, 0, ft_strchr(temp, ' ') - temp);
	close(fd);
	return (pid);
}
