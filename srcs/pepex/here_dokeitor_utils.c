/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dokeitor_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:57:32 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/27 20:58:16 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*filename_generator(void)
{
	static int	index_filename = 0;
	char		*file_temp;
	char		*number_conv;

	number_conv = ft_itoa(index_filename++);
	if (!number_conv)
		return (NULL);
	file_temp = ft_strjoin("/tmp/tempfile", number_conv);
	free(number_conv);
	return (file_temp);
}

int	heredoc_father(int heredoc_fd)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	wait(&status);
	close(heredoc_fd);
	return (WEXITSTATUS(status));
}

char	*ft_clean_delimiter(char *delimiter)
{
	int		i;
	int		j;
	char	quote;
	char	*clean_delimiter;

	i = 0;
	j = 1;
	clean_delimiter = ft_calloc(ft_strlen(delimiter), sizeof(char) + 2);
	while (delimiter[i])
	{
		if (ft_strchr(QUOTES, delimiter[i]))
		{
			quote = delimiter[i];
			while (delimiter[++i] && delimiter[i] != quote)
				clean_delimiter[j++] = delimiter[i];
			i++;
		}
		else
			clean_delimiter[j++] = delimiter[i++];
	}
	if (i == (j - 1))
		clean_delimiter[0] = EXPAND;
	else
		clean_delimiter[0] = DONT_EXPAND;
	return (clean_delimiter);
}
