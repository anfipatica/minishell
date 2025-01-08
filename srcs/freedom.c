
#include "minishell.h"

void	freedom_error_fresh_token(t_token *head_token, char *line, t_env *env)
{
		free(line);
		ft_free_tokens(head_token);
		ft_free_env(env);
		exit(13);
}