#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	argv = NULL;
	if (argc != 1)
		return (1);
	copy_env(env);
	promptereitor(env);
	return (0);
}

// 
// SOLUCIONAR $$ !!!!!!! -> ps | grep "bash" | awk {print'$1'}
