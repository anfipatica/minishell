#include "minishell.h"

void	child_signal_handler(int signal)
{
	write(1, "\n", 1);
}
void	father_signal_handler(int signal)
{
	write(1, "\n", 1);
	rl_replace_line("", false);
	rl_on_new_line();
	rl_redisplay();
}
