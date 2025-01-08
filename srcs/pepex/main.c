/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:04:12 by psapio            #+#    #+#             */
/*   Updated: 2024/12/04 21:53:53 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "pipex.h"
// #define WRITE 1
// #define READ 0

// int	pipex(t_command *command_list, t_env *envp)
// {
// 	int		p_fds[2];
// 	int		status;
// 	pid_t	last;

	// if (argc != 5)
	// 	print_error("Usage: ./pipex file1 cmd1 cmd2 file2\n");
// 	if (pipe(p_fds) == -1)
// 		return (1);
// 	child_pepe_first(p_fds, argv[2], argv[1], envp);
// 	last = child_paolo_last(p_fds, argv, argc, envp);
// 	close(p_fds[WRITE]);
// 	close(p_fds[READ]);
// 	waitpid(last, &status, 0);
// 	waitpid(-1, NULL, 0);
// 	return ((char)(status >> 8));
// }
// interesting:
// man waitpid
// /./pipex infile "sleep 3" ls /dev/stdout
