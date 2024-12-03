#include "minishell.h"

int	main(int argc, char **argv, char **env_original)
{
	t_env	*env;

	(void)argv;
	if (argc != 1)
		return (1);
	env = copy_env(env_original);
	promptereitor(env);
	ft_free_env(env);
	return (0);
}

//TODO	clasificar las palabras
//TODO	tenemos que implementar las multiridirecions del pipex;
//TODO	hacer los buldings que son relativamente faciles
//TODO	implementar las siñales
//TODO	incrustrarle el pipex que funcione!
//- 	LO TENEMOS!