
#include "minishell.h"

void	freedom_error_fresh_token(t_list *head_token, char *line, t_list *env)
{
		free(line);
		ft_lstiter(head_token, ft_free_one_token);
		ft_lstiter(env, ft_free_env);
		exit(13);
}