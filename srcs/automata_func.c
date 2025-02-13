#include "minishell.h"


int	insert_args(t_backpack *backpack)
{
	t_token	*token;

	token = backpack->token;
	if (!backpack->last_command)
	{
		backpack->last_command = new_command(backpack->env);
		add_command_back(&(backpack->head_command), backpack->last_command);
	}
	backpack->arg_aux = new_args(ft_ternary(token->expanded, token->expanded, token->str));
	add_args_back(&(backpack->last_command->args), backpack->arg_aux);
	return (0);
}

int	set_redirect_type(t_backpack *backpack)
{
	t_token	*token;

	token = backpack->token;
	if (!backpack->last_command)
	{
		backpack->last_command = new_command(backpack->env);
		add_command_back(&(backpack->head_command), backpack->last_command);
	}
	backpack->redirect_aux = new_redirect(token->type);
	add_redirect_back(&(backpack->last_command->head_redirect), backpack->redirect_aux);
	return (0);
}

int	insert_file(t_backpack *backpack)
{
	t_token	*token;

	token = backpack->token;
	if (backpack->redirect_aux->redirect_type == T_HERE_DOC)
		backpack->redirect_aux->name = token->str;
	else
		backpack->redirect_aux->name = ft_ternary(token->expanded, token->expanded, token->str);
	return (0);
}

int	end_command(t_backpack *backpack)
{
	backpack->last_command = NULL;
	return (0);
}

int	syntax_error(t_backpack *backpack)
{
	write(2, RED"SYNTAX ERROR\n"STD, 24);
	ft_free_commands(backpack->head_command);
	return (ERROR__STATE);
}
// ls -la > file | grep hello > file2