#include "minishell.h"
	t_env *create_node_env(void);

int	main(int argc, char **argv, char **env)
{
	create_node_env();

	argv = NULL;
	if (argc != 1)
		return (1);
	//copy_env(env);
	promptereitor(env);
	return (0);
}

// 
// SOLUCIONAR $$ !!!!!!! -> ps | grep "bash" | awk {print'$1'}
