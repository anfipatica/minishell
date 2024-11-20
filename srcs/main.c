#include "minishell.h"

int	main(int argc, char **argv, char **env_original)
{
	t_env *env;

	argv = NULL;
	if (argc != 1)
		return (1);
	env = copy_env(env_original);
	promptereitor(env_original);
	ft_free_env(env);
	return (0);
}

// 
// SOLUCIONAR $$ !!!!!!! -> ps | grep "bash" | awk {print'$1'}
