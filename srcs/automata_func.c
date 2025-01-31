#include "minishell.h"

/* int	insert_command(t_token	*token, t_command *command)
{
	ddddprintf(2, 2, 2, 2, "holaaaa!\n");
	if (command->path_command)
		return (insert_args(token, command));
	dprintf(2, "INSERT_COMMAND\n");
	command->path_command = find_path_name(ft_ternary(token->expanded, token->str, token->expanded), command->env, NULL);
	insert_args(token, command);
	return (0);
} */

int	insert_args(t_token	*token, t_command *command)
{
	t_args	*aux_arg;
	aux_arg = new_args(ft_ternary(token->expanded, token->str, token->expanded));
	add_args_back(&(command->args), aux_arg);
	return (0);
}

int	set_redirect_type(t_token	*token, t_command *command)
{
	command->aux_redirect = new_redirect(token->type);
	add_redirect_back(&(command->head_redirect), command->aux_redirect);
	return (0);
}

int	insert_file(t_token	*token, t_command *command)
{
	command->aux_redirect->name = ft_ternary(token->expanded, token->str, token->expanded);
	return (0);
}

int	end_command(t_token	*token, t_command *command)
{
	(void) command;
	(void) token;
	return (0);
}

int	sintax_error(t_token	*token, t_command *command)
{
	dprintf(2, RED"SINTAX_ERROR\n"STD);
	(void) token;
	(void) command;
	return (ERROR__STATE);
}
// ls -la > file | grep hello > file2