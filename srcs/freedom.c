
#include "minishell.h"
#include <assert.h>

void	free_all(t_command *command)
{
	if (command->execve_matrix && *(command->execve_matrix))
	{
		free(command->execve_matrix[ARGS]);
		free_double_pointer(command->execve_matrix[ENV]);
	}
	ft_free_env(command->env);
	ft_free_tokens(command->token_pointer);
	ft_free_commands(command);
	// command = NULL;
}

void	freedom_error_fresh_token(t_token *head_token, char *line, t_env *env)
{
	free(line);
	ft_free_tokens(head_token);
	ft_free_env(env);
	// assert(0);
	exit(13);
}

void	free_exit_execution(char *path_name, char **matrix[2])
{
	free(path_name);
	free(matrix[ARGS]);
	free_double_pointer(matrix[ENV]);

	exit(99);
}