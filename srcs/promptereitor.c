
#include "minishell.h"

int	promptereitor(t_env *env)
{
	char	*line;
	t_token	*first_token;

	first_token = NULL;
	while (1)
	{
		line = readline("Prompt > ");
		twin_quote(line);
		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			first_token = tokenizer(line, env);
			print_tokens(first_token);
			ft_free_tokens(first_token);
			free(line);
		}
	}
	free(line);
	rl_clear_history();
	return (0);
}

