#include "minishell.h"

/**
 * This function emulates getenv with our own t_env env.
 * It will search name inside the list, returning the value if found. NULL if not.
 */
t_env *create_node_env(char *line_env)
{
	t_env	*env_node;
	char	*name;
	char	*value;
	char	*igual_position;

	igual_position = ft_strchr(line_env, '=');
	name = ft_substr(line_env, 0, igual_position - line_env);
	value = ft_substr(line_env, igual_position - line_env + 1, ft_strlen(igual_position));
	env_node = new_env(name, value);
	return (env_node);
}

t_env *copy_env(char **env)
{
	t_env *head_list;
	t_env *new_node;
	int i;

	head_list = NULL;
	i = 0;
	while (env[i])
	{
		new_node = create_node_env(env[i]);
		add_env_back(&head_list, new_node);
		i++;
	}
	return (head_list);
}

char	*ft_getenv(char *name, t_env *env, int length)
{
	int	str_len;
	
	if (length != 0)
		str_len = length;
	else
		str_len = ft_strlen(name);
	dprintf(2, "name var: %s\n", name);
	while (env)
	{
		if (ft_strncmp(name, env->name, str_len) == 0 && env->name[str_len] == 0)
			return (env->value);
		env = env->next;
	}
	dprintf(2, "No se ha encontrado %s\n", name);
	return (NULL);
}