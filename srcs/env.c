#include "minishell.h"

/**
 * This function emulates getenv with our own t_env env.
 * It will search name inside the list, returning the value if found. NULL if not.
 */
char	*ft_getenv(char *name, t_env *env, int length)
{
	int	str_len;
	if (length != 0)
		str_len = length;
	else
		str_len = ft_strlen(name);
	while (env)
	{
		if (ft_strncmp(name, env->name, str_len) == 0)
			return (env->value);
		env = env->next;
	}
	printf("No se ha encontrado %s\n", name);
	return (NULL);
}