#include "minishell.h"

int	main(int argc, char **argv, char **env_original)
{
	t_list	*list_env;

	(void)argv;
	if (argc != 1)
		return (1);
	list_env = copy_env(env_original);
	promptereitor(list_env);
	ft_lstclear(&list_env, ft_free_env);
	return (0);
}
////	da segfoul: revisar list check
//TODO continua modificar las listas desde el list check
//TODO abrazar a yolanda!

//TODO	clasificar las palabras
//TODO	tenemos que implementar las multiridirecions del pipex;
//TODO	hacer los buldings que son relativamente faciles
//TODO	implementar las siñales
//TODO	incrustrarle el pipex que funcione!
//- 	LO TENEMOS!