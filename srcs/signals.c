#include "minishell.h"

/*
ctrl + c: Imprime una nueva entrada en una línea nueva.
	No cierra la minishell, sólo cancela el prompt que se esté ejecutando
ctrl + d: Termina el shell actual = exit.
	Si hay 2 minishells abiertas,ctrl + d cierra sólo la última abierta.
ctrl + /: Nada
*/


/*
	*sa.sa_handler == sa.__sigaction_handler.sa_handler:
	*Según sigaction.h:

	.- Signal handler.
	#if defined __USE_POSIX199309 || defined __USE_XOPEN_EXTENDED
	    union
	      {
		.// Used if SA_SIGINFO is not set.
		__sighandler_t sa_handler;
		.// Used if SA_SIGINFO is set.
		void (*sa_sigaction) (int, siginfo_t *, void *);
	      }
	    __sigaction_handler;
	# define sa_handler	__sigaction_handler.sa_handler
	# define sa_sigaction	__sigaction_handler.sa_sigaction
	#else
	    __sighandler_t sa_handler;
	#endif
 */


void	father_signal_handler(int signal, siginfo_t *info, void *ucontext)
{
	(void)signal;
	(void)ucontext;
	if (info->si_pid == CHILD)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", false);
	rl_redisplay();
	//? NO sé por qué pero funciona yuhuuu

}

void	child_signal_handler(int signal)
{
	printf("\n");
	(void)signal;
	exit(130);
}

void	child_signal_listener()
{
	struct sigaction	sa;
	sigset_t				mask;

	sigemptyset(&mask);
	sa.sa_handler= child_signal_handler;
	sa.sa_mask = mask;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	father_signal_listener()
{
	struct sigaction	sa;
	sigset_t				mask;

	sigemptyset(&mask);
	sa.sa_sigaction= father_signal_handler;
	sa.sa_mask = mask;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
}