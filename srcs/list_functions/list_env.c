#include "minishell.h"

size_t len_list_env(t_env *list)
{
	size_t i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char **lts_env_to_matrix(t_env *env)
{
	char	**env_matrix;
	char	*name_aux;;
	int	i;

	env_matrix = malloc((len_list_env(env) + 1) * sizeof(char *));
	if (!env_matrix)
		return(NULL);
	i = 0;
	while (env)
	{
		name_aux = ft_strjoin(env->name, "=");
		env_matrix[i] = ft_strjoin(name_aux, env->value);
		if (!env_matrix[i] || !name_aux)
			return (free_double_pointer(env_matrix), NULL);
		free(name_aux);
		i++;
		env = env->next;
	}
	env_matrix[i] = NULL;
/* 	for (int j = 0; env_matrix[j]; ++j)
		printf("env_matrix = %s\n", env_matrix[j]); */
	return (env_matrix);
}

void	print_env(t_env *env)
{
	printf("\n╭━━━┈┈<⭒.⋆🪐 𝕊𝕋𝔸ℝ𝕋 ✨˚⋆.>┈┈━━━╮\n");
	while (env)
	{
		printf("name: %s - value: %s\n", env->name, env->value);
		env = env->next;
	}
	printf("\n╰☆┈☆┈☆┈☆┈< 🌙 𝐹𝐼𝒩 🌌 >┈☆┈☆┈☆┈☆╯\n\n");
}

/**
 * new_env creates a new token and allocates memory for it.
 */
t_env	*new_env(char *name, char *value)
{
	t_env	*new_env;

	new_env = ft_calloc(sizeof(t_env), 1);
	if (!new_env)
		return (NULL);
	new_env->name = name;
	new_env->value = value;
	new_env->next = NULL;
	return (new_env);
}

/**
 * add_env_back receives the head of the list and the new token
 * to add at the end of said list. If there is no head, new becomes it.
 */
void	add_env_back(t_env **head_list, t_env *new_node)
{
	t_env	*temp;

	if (*head_list == NULL)
	{
		*head_list = new_node;
	}
	else
	{
		temp = *head_list;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_node;
	}
}

/**
 * ft_free_env frees the nodes of a list and the neccesary content
 * inside each of them.
 */
void	ft_free_env(t_env *env)
{
	t_env	*temp;

	if (!env)
		return ;
	while (env != NULL)
	{
		free(env->name);
		free(env->value);
		temp = env->next;
		free(env);
		env = temp;
	}
}
