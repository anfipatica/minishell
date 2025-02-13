
#include "minishell.h"

int g_exit_status = 0;

int	main(int argc, char **argv, char **env_original)
{
	t_env	*env;

	(void)argv;
	if (argc != 1)
		return (1);
	signal(SIGQUIT, SIG_IGN);
	env = copy_env(env_original);
	promptereitor(env);
	ft_free_env(env);
	return (0);
}

////	clasificar las palabras
////  generador de nombre de archivos

//TODO	hacer los buldings que son relativamente faciles
//TODO	implementar las siñales
//TODO	incrustrarle el pipex que funcione!

//- 	LO TENEMOS!