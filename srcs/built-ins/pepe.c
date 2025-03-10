/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pepe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:40:13 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/03/05 17:51:46 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	valgrind --trace-children=yes /bin/usr/curl parrot.live
*/

/*
	This built-in shows the happines of pepe <3
*/
void	pepe(void)
{
	const char	*cmd[] = {"/usr/bin/curl", "parrot.live", NULL};
	int			pid;
	int			status;

	signal(SIGINT, child_signal_handler);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd[0], (char **)cmd, NULL);
		perror(cmd[0]);
		exit(1);
	}
	waitpid(pid, &status, 0);
}

#define CACA \
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠋⠀⠉⠉⠳⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡞⠀⠀⠀⠀⠀⠀⠘⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠆⠀⠀⠀⠀⣠⠖⠊⡞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠤⡵⠈⠉⠁⠀⠀⠀⠀⠉⢓⡦⡀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡤⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡤⠋⠁⠀⢹⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⣠⡖⠯⠤⠤⣀⡀⠀⠀⡇⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣧⠔⠂⠒⠢⡒⠉⡜⠁⠀⡏⣤⣄⣹⠀⠀⠙⣯⡀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⣠⢼⠇⣮⣭⡇⠀⢸⠀⠇⠀⠀⠓⠭⡏⠁⠀⠀⢀⡞⠉⢦⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⢶⠉⠀⢨⠀⠉⠁⠀⠀⡏⠀⡠⠗⠤⡤⠤⠤⠤⠆⠊⠁⠀⠀⠀⢹⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠧⠤⠖⠋⡩⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡆⠀⠀\n\
⠀⠀⠀⠀⠀⠀⡇⡀⠄⠄⠤⠤⠂⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡎⠀⠀⠀\n\
⠀⠀⠀⠀⠤⠾⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡏⠀⠀⠀⠀\n\
⠀⠀⠀⠀⣸⠀⠀⠀⠀⠀⠀⠀⢀⠤⠤⠤⠤⠄⠄⠤⠀⠄⠄⠤⢄⠄⠀⠀⠀⣨⠷⡄⠀⠀\n\
⢠⠖⠉⠁⠀⠀⠀⠀⠀⠀⠀⠈⢣⡀⠀⠀⠀⠀⠀⠀⢀⡴⠋⠁⠀⠀⡠⠊⠁⠀⠀⢹⡀⠀\n\
⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⠂⠒⠒⠋⠁⠀⠀⠀⢠⠖⠁⠀⠀⠀⠀⠀⠘⡆\n\
⠈⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡤⠒⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱\n\
⠀⠀⠉⠓⠤⡀⣀⣀⡀⡀⡀⣀⡠⡠⠔⠒⠊⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠠⠤⠞⠁\n\
⠀⠀⠀⠀⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⠈⠂⠒⠠⠀⠠⠀⠠⠀⠀⠂⠐⠀⠁⠀⠀⠀⠀"

void	caca(void)
{
	printf("%s\n", CACA);
}

void	segfault(void)
{
	printf("[1]    2740644 segmentation fault (core dumped) ./mimishell\n");
}

#define AUGUSTIN "\
           (¯)\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |BBBBBBBBBBBBBBWWWWWWWWWWWWWWRRRRRRRRRRRRRR\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |			B = BLEU\n\
           | |			W = BLANC\n\
           | |			R = ROUGE\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
      _____|_|_____\n\
     /             \\\n\
    /     Vive      \\\n\
   /       la        \\\n\
  /      France !     \\\n\
 /                     \\\n\
/_______________________\\\n"

/* #define AUGUSTIN "\
           (¯)\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |"BLUE"BBBBBBBBBBBBBB"STD"WWWWWWWWWWWWWW"RED"RRRRRRRRRRRRRR"STD"\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
           | |\n\
      _____|_|_____\n\
     /             \\\n\
    /     Vive      \\\n\
   /       la        \\\n\
  /      France !     \\\n\
 /                     \\\n\
/_______________________\\\n" */

void	augustin(void)
{
	printf("%s\n", AUGUSTIN);
}
