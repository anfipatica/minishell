/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:19:08 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/03/05 17:52:26 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_exit_status = 0;

int	main(int argc, char **argv, char **env_original)
{
	t_env	*env;

	(void)argv;
	if (argc != 1)
	{
		write(2, RED"ERROR: Too many arguments\n"STD, 37);
		return (1);
	}
	signal(SIGQUIT, SIG_IGN);
	env = copy_env(env_original);
	promptereitor(env);
	ft_free_env(env);
	return (0);
}
