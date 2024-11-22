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

//darle una vuelta a expand_d_quote en quoteitor.c