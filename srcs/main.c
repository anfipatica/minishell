#include "minishell.h"

int	main(int argc, char **env)
{
	env = NULL;
	if (argc != 1)
		return (1);
	promptereitor(env);
	return (0);
}

// 
// SOLUCIONAR $$ !!!!!!! -> ps | grep "bash" | awk {print'$1'}
