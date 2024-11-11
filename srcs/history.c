
#include "../inc/minishell.h"

int	promptereitor(void)
{
	char	*line;
	t_token	*token;
	t_token	*first_token;

	first_token = NULL;
	while (1)
	{
		line = readline("Prompt > ");
		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		if (line[0] != '\0')
			add_history(line);
		token = tokenizer(line);
		add_token_back(&first_token, token);
		free(line);
	}
	go_over_list(first_token);
	ft_free_list(first_token);
	free(line);
	rl_clear_history();
	return (0);
}

