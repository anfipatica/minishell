#include "minishell.h"

// /**
//  * This function only prints the context of the list, useful for debugging
//  */
// void	print_env(t_env *env)
// {
// 	printf("\n╭━━━┈┈<⭒.⋆🪐 𝕊𝕋𝔸ℝ𝕋 ✨˚⋆.>┈┈━━━╮\n");
// 	while (env)
// 	{
// 		printf("name: %s - value: %s\n", env->name, env->value);
// 		env = env->next;
// 	}
// 	printf("\n╰☆┈☆┈☆┈☆┈< 🌙 𝐹𝐼𝒩 🌌 >┈☆┈☆┈☆┈☆╯\n\n");
// }

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
	return (new_env);
}


/**
 * ft_free_env frees the nodes of a list and the neccesary content
 * inside each of them.
 */
void	ft_free_env(void *content)
{
	t_env	*env = (t_env *)content;
	if (!env)
		return ;
	free(env->name);
	free(env->value);
	free(env);
}
