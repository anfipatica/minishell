#include "minishell.h"

t_env *copy_env(char **env)
{
	int		i;
	int		k;
	t_env	*env_node;
	char	**temp_split;

	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);


	i = 0;
	while (env[i] != NULL)
	{
		temp_split = ft_split(env[i], '=');
		k = 0;
		env_node->name = temp_split[0];
		env_node->value =  temp_split[1];
		i++;
	}
	printf("env_node->name: %s\n", env_node->name);
	printf("env_node->value: %s\n", env_node->value);
}