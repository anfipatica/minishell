/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:02:15 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/27 18:08:21 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	insert_args(t_backpack *bp)
{
	t_token	*token;

	token = bp->token;
	if (!bp->last_command)
	{
		bp->last_command = new_command(bp->env, bp->head_token);
		add_command_back(&(bp->head_command), bp->last_command);
	}
	bp->arg_aux = new_args(ft_ternary
			(token->expanded, token->expanded, token->str));
	add_args_back(&(bp->last_command->args), bp->arg_aux);
	return (0);
}

int	set_redirect_type(t_backpack *bp)
{
	t_token	*token;

	token = bp->token;
	if (!bp->last_command)
	{
		bp->last_command = new_command(bp->env, bp->head_token);
		add_command_back(&(bp->head_command), bp->last_command);
	}
	bp->redirect_aux = new_redirect(token->type);
	add_redirect_back(&(bp->last_command->head_redirect), bp->redirect_aux);
	return (0);
}

int	insert_file(t_backpack *bp)
{
	t_token	*token;

	token = bp->token;
	bp->redirect_aux->name = ft_ternary
		(token->expanded, token->expanded, token->str);
	return (0);
}

int	end_command(t_backpack *bp)
{
	bp->last_command = NULL;
	return (0);
}

int	syntax_error(t_backpack *bp)
{
	write(2, RED"SYNTAX ERROR\n"STD, 24);
	ft_free_commands(bp->head_command);
	return (ERROR__STATE);
}
