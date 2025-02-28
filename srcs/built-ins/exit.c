/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <psapio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:00:05 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/28 19:31:53 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

bool	does_overflow_unsigned_int(char *max_number)
{
	int		i;
	char	*max_num_changed;

	i = 0;
	max_num_changed = ft_ltoa(ft_atol(max_number));
	if (*max_number == '+')
		max_number++;
	while (*max_number && max_number[0] == '0')
		max_number++;
	if (ft_strcmp(max_number, max_num_changed) == 0)
	{
		free(max_num_changed);
		return (false);
	}
	free(max_num_changed);
	return (true);
}

bool	check_if_valid_exit_code(t_command *command, t_args *aux_head)
{
	if (ft_strisdigit(command->args->name) == false
		|| does_overflow_unsigned_int(command->args->name) == true)
	{
		ft_free_one_args(aux_head);
		error_exit(command->args->name, EXIT_NON_DIGIT, command);
	}
	else if (command->args->next != NULL)
	{
		write(2, "exit: too many arguments\n", 26);
		ft_free_one_args(aux_head);
		g_exit_status = 1;
		return (false);
	}
	return (true);
}

//max signed 64-bit integer: 9223372036854775807
void	ft_exit(t_command *command)
{
	t_args	*aux_head;
	int		return_number;

	if (!command->args->next || command->next)
		exit(OK);
	aux_head = command->args;
	command->args = command->args->next;
	if (check_if_valid_exit_code(command, aux_head) == false)
		return ;
	else
	{
		return_number = ft_atoi(command->args->name);
		command->args = aux_head;
		free_all(command);
		exit((unsigned char)return_number);
	}
}
