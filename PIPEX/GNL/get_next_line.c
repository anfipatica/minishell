/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:41:01 by psapio            #+#    #+#             */
/*   Updated: 2024/01/22 12:43:54 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//#define BUFFER_SIZE	BUFFER_SIZE
/*
void	leaks(void)
{
	system("leaks -q a.out");
}*/

static int	counter_n0_str(char	*str)
{
	int	i;

	i = 0;
	while ((str[i] != '\n') && (str[i] != '\0'))
		i++;
	return (i);
}

static void	trip_ny(t_data *data, char **ellis)
{
	char	*aux;
	int		start_position;

	aux = *ellis;
	data->new_york = ft_substr(*ellis, 0, (counter_n0_str(*ellis) + 1));
	start_position = counter_n0_str(*ellis) + 1;
	*ellis = ft_substr(*ellis, start_position, ft_strlen(*ellis));
	free(aux);
}

static char	*loop(int fd, t_data *data, char **ellis)
{
	int	boat_captain_report;

	boat_captain_report = 1;
	while (boat_captain_report > 0)
	{
		boat_captain_report = read(fd, data->sicily, BUFFER_SIZE);
		if (boat_captain_report == -1)
		{
			if (*ellis)
				free(*ellis);
			return (*ellis = NULL, NULL);
		}
		data->sicily[boat_captain_report] = '\0';
		data->aux = *ellis;
		*ellis = ft_strjoin(*ellis, data->sicily);
		free(data->aux);
		if ((ft_strchr(*ellis, '\n')) || (boat_captain_report == 0))
		{
			trip_ny(data, ellis);
			if (data->new_york[0] == '\0')
				return (free(*ellis),*ellis = NULL, free(data->new_york), NULL);
			return (data->new_york);
		}
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	t_data		data;
	static char	*ellis;

	if (fd < 0)
		return (NULL);
	if (ellis == NULL)
	{
		ellis = malloc(1);
		if (!ellis)
			return (NULL);
		ellis[0] = '\0';
	}
	return (loop(fd, &data, &ellis));
}
/*
//#ifdef MAIN
int main (int argc, char **argv)
{
	int fd;
	char *line;
	int i;

//	atexit(leaks);

	if (argc < 2)
	{
		printf("Error!\n");
		return 1;
	}
	++argv;
	while (*argv)
	{
		fd = open(*argv, O_RDONLY);
		printf("\nOpen '%s' file\n", *argv);
		i = 0;
		while ((line = get_next_line(fd)))
		{
			printf("%i, line: %s", i, line);
			free(line);
			i++;
		}
		close(fd);
		printf("\nClose '%s' file\n", *argv);
		++argv;
	}
}
//#endif
*/
