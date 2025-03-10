/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:26:43 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/03/05 18:11:57 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_var_name(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]) == 1)
		return (false);
	if (ft_isalpha(name[0]) == 0 && name[0] != '_')
		return (false);
	i = 1;
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	if_exist_var_overwrite(t_env *env, t_env *var)
{
	while (env)
	{
		if (ft_strcmp(env->name, var->name) == 0)
		{
			free(env->value);
			if (var->value)
				env->value = ft_strdup(var->value);
			else
				env->value = NULL;
			ft_free_one_env(var);
			return (true);
		}
		env = env->next;
	}
	return (false);
}

void	print_export(t_command *command)
{
	while (command->env)
	{
		if (command->env->value == NULL)
			printf("declare -x %s\n", command->env->name);
		else
		{
			printf("declare -x %s=\"%s\"\n",
				command->env->name, command->env->value);
		}
		command->env = command->env->next;
	}
}

int	ft_export(t_command *command)
{
	t_env		*var;
	t_args		*arg;
	bool		error;

	arg = command->args->next;
	error = false;
	if (arg == NULL)
		return (print_export(command), 0);
	while (arg)
	{
		var = create_node_env(arg->name);
		if (!var)
		{
			print_error(arg->name, INVALID_EXPORT_IDENTIFIER);
			error = true;
			g_exit_status = 1;
		}
		else if (if_exist_var_overwrite(command->env, var) == false)
		{
			add_env_back(&command->env, var);
		}
		arg = arg->next;
	}
	return (error);
}
