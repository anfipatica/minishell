#include "minishell.h"

t_env *create_node_env(char *line_env)
{
	t_env	*env_node;
	char	*name;
	char	*value;
	char	*igual_position;

	igual_position = ft_strchr(line_env, '=');
	if (igual_position == NULL)
	{
		name = ft_substr(line_env, 0, ft_strlen(line_env));
		value = NULL;
	}
	else
	{
		name = ft_substr(line_env, 0, igual_position - line_env);
		value = ft_substr(line_env, igual_position - line_env + 1, ft_strlen(igual_position));
	}
	if (valid_var_name(name) == false)
	{
		free(name);
		free(value);
		return (NULL);
	}
	env_node = new_env(name, value);
	return (env_node);
}

t_env *copy_env(char **env_original)
{
	t_env	*head_list;
	t_env	*new_node;
	char	*sh_level;
	int 	i;

	head_list = NULL;
	i = 0;
	while (env_original[i])
	{
		new_node = create_node_env(env_original[i]);
		if (ft_strcmp(new_node->name, "SHLVL") == 0)
		{
			sh_level = new_node->value;
			new_node->value = ft_itoa((ft_atoi(new_node->value) + 1));
			free(sh_level);
		}
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
	while (env)
	{
		if (ft_strncmp(name, env->name, str_len) == 0 && env->name[str_len] == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
