#include "minishell.h"


void	insert_arg(t_backpack *backpack, char* arg)
{
	t_token	*token;

	if (!backpack->last_command)
	{
		backpack->last_command = new_command(backpack->env);
		add_command_back(&(backpack->head_command), backpack->last_command);
	}
	backpack->arg_aux = new_args(arg);
	add_args_back(&(backpack->last_command->args), backpack->arg_aux);
}
int	insert_args(t_backpack *backpack)
{
	t_token	*token;
	char **split;
	int		i;
		print_tokens(backpack->token);
		printf("ENV!!!!\n");

	token = backpack->token;
	if (token->type == T_ENV)
	{
		split = ft_split(token->expanded, ' ');
		i = 0;
		while (split[i])
		{
			insert_arg(backpack, split[i]);
			free(split[i]);
			backpack->last_command = new_command(backpack->env);
			add_command_back(&(backpack->head_command), backpack->last_command);

			i++;
		}
		free(split);
	} else {
		insert_arg(backpack, ft_ternary(token->expanded, token->expanded, token->str));
	}
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