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