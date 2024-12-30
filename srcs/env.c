#include "minishell.h"

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

t_list *copy_env(char **env)
{
	t_list *head_list;
	t_list *new_node;
	int i;

	head_list = NULL;
	i = 0;
	while (env[i])
	{
		new_node = ft_lstnew(create_node_env(env[i]));
		ft_lstadd_back(&head_list, new_node);
		i++;
	}
	return (head_list);
}

bool	find_env(void *content, void *context)
{
	if (ft_strcmp(((t_env *)content)->name, context) == 0)
		return (true);
	return (false);
}

/**
 * This function emulates getenv with our own t_env env.
 * It will search name inside the list, returning the value if found. NULL if not.
 */
char	*ft_getenv(char *name, t_list *env, int length)
{
	int	str_len;
	t_env	*ok_env;

	if (length != 0)
		str_len = length;
	else
		str_len = ft_strlen(name);
	printf("name var: %s\n", name);
	ok_env = ft_lstfind(env, name, find_env);
	if (ok_env)
		return (ok_env->value);
	return (NULL);
}