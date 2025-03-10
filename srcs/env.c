/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:18:13 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/03/03 19:06:11 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_node_env(char *line_env)
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
		value = ft_substr(line_env, igual_position - line_env + 1,
				ft_strlen(igual_position));
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

void	create_own_env(t_env **head_node, t_env *new_node)
{
	char	*pwd_aux;
	char	*join_aux;

	pwd_aux = getcwd(NULL, 0);
	join_aux = ft_strjoin("PWD=", pwd_aux);
	*head_node = create_node_env("SHLVL=1");
	new_node = create_node_env(join_aux);
	add_env_back(head_node, new_node);
	free(pwd_aux);
	free(join_aux);
}

t_env	*copy_env(char **env_original)
{
	t_env	*head_list;
	t_env	*new_node;
	char	*sh_level;
	int		i;

	head_list = NULL;
	i = 0;
	new_node = NULL;
	if (!(*env_original))
		create_own_env(&head_list, new_node);
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

/**
 * ft_getenv is our version of getenv, useful to expand the input line.
 * You can send the character right after a $ was found and the length till
 * a space char (or null) is found.
 * If length is 0, length will be updated with the length of name.
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
		if (ft_strncmp(name, env->name, str_len) == 0
			&& env->name[str_len] == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
