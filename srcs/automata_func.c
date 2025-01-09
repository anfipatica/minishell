#include "minishell.h"

/* int	insert_command(t_token	*token, t_command *command)
{
	// printf("holaaaa!\n");
	// if (command->path_command)
	// 	return (insert_args(token, command));
	// printf("INSERT_COMMAND\n");
	// command->path_command = find_path_name(ft_ternary(token->expanded, token->str, token->expanded), command->env, NULL);
	insert_args(token, command);
	return (0);
} */

int	insert_args(t_token	*token, t_command *command)
{
	printf("INSERT_FLAG\n");
	t_args	*aux_arg;
	aux_arg = new_args(ft_ternary(token->expanded, token->str, token->expanded));
	add_args_back(&(command->args), aux_arg);
	return (0);
}

int	set_redirect_type(t_token	*token, t_command *command)
{

	printf("SET_REDIRECT_TYPE\n");
	command->aux_redirect = new_redirect(token->type);
	return (0);
}

int	insert_file(t_token	*token, t_command *command)
{
	printf("INSERT_FILE\n");
	command->aux_redirect->name = ft_ternary(token->expanded, token->str, token->expanded);
	add_redirect_back(&(command->redirect), command->aux_redirect);
	return (0);
}

int	end_command(t_token	*token, t_command *command)
{
	printf("END_COMMAND\n");
	(void) token;
	(void) command;
	return (0);
}

int	sintax_error(t_token	*token, t_command *command)
{
	printf(RED"SINTAX_ERROR\n"STD);
	(void) token;
	(void) command;
	return (ERROR__STATE);
}