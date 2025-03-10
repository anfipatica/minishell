/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:16:01 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/03/10 12:37:25 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_command *command)
{
	int			i;
	const char	*builtins[] = {
		"cd", "echo", "env", "exit", "export",
		"pwd",
		"unset",
		"caca",
		"augustin",
		"version",
		"jacobo",
		NULL
	};

	i = 0;
	if (!command->args)
		return (false);
	while (builtins[i] != NULL)
	{
		if (ft_strcmp(command->args->name, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	exec_builtin_thanks(t_command *command)
{
	if (ft_strcmp(command->args->name, "kermit") == false)
		return (kermit(), true);
	if (ft_strcmp(command->args->name, "pepe") == false)
		return (pepe(), true);
	if (ft_strcmp(command->args->name, "caca") == false)
		return (caca(), true);
	if (ft_strcmp(command->args->name, "segfault") == false)
		return (segfault(), true);
	if (ft_strcmp(command->args->name, "augustin") == false)
		return (augustin(), true);
	if (ft_strcmp(command->args->name, "guillaume") == false)
		return (augustin(), true);
	if (ft_strcmp(command->args->name, "version") == false)
		return (version(), true);
	if (ft_strcmp(command->args->name, "jacobo") == false)
		return (jacobo(), true);
	return (false);
}

bool	exec_builtin(t_command *command)
{
	if (!command->args)
		return (1);
	if (ft_strcmp(command->args->name, "cd") == false)
		return (ft_cd(command), true);
	if (ft_strcmp(command->args->name, "echo") == false)
		return (ft_echo(command), true);
	if (ft_strcmp(command->args->name, "env") == false)
		return (ft_env(command), true);
	if (ft_strcmp(command->args->name, "exit") == false)
		return (ft_exit(command), true);
	if (ft_strcmp(command->args->name, "export") == false)
		return (ft_export(command), true);
	if (ft_strcmp(command->args->name, "pwd") == false)
		return (ft_pwd(command->env), true);
	if (ft_strcmp(command->args->name, "unset") == false)
		return (ft_unset(command), true);
	return (exec_builtin_thanks(command));
}
