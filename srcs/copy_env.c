#include "minishell.h"


t_env *create_node_env(void)
{
	char *line_env = "HOME=/home/ymunoz-m";
	t_env	*env_node;
	char *name;
	char *value;
	char *igual_position;

	igual_position = ft_strchr(line_env, '=');
	name = ft_substr(line_env, 0, igual_position - line_env);
	value = ft_substr(line_env, igual_position - line_env + 1, ft_strlen(igual_position));

	printf("name: %s\n", name);
	printf("value: %s\n", value);
	//env_node = new_env()
}

// t_env *copy_env(char **env)
// {
// 	int i
// 	create_node_env(env[i]);
// }