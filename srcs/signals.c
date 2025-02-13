#include "minishell.h"

void	child_signal_handler(int signal)
{
	write(1, "\n", 1);
}

void	heredoc_signal_handler(int signal)
{
	write(1, "\n", 1);
	//close(3); //!Esto es un poo guarrete, bash deja el fd abierto así que a ver qué opina pepex
	exit(130);
}

void	father_signal_handler(int signal)
{
	write(1, "\n", 1);
	rl_replace_line("", false);
	rl_on_new_line();
	rl_redisplay();
}
