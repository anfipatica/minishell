#include "minishell.h"
	t_env *create_node_env(void);

int	main(int argc, char **argv, char **env_original)
{
	t_env *env;

	argv = NULL;
	if (argc != 1)
		return (1);
	env = copy_env(env_original);
	print_env(env);
	promptereitor(env_original);
	ft_free_env(env);
	return (0);
}

// 
// SOLUCIONAR $$ !!!!!!! -> ps | grep "bash" | awk {print'$1'}
