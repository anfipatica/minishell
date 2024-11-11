
#include "../inc/minishell.h"

int	promptereitor(void)
{
	char	*line;
	line = readline("Prompt > ");
	while (ft_strncmp(line, "q", 2) != 0)
	{
		if (line[0] != '\0')
			add_history(line);
		rl_on_new_line();
		free(line);
		line = readline("Prompt > ");
	}
	free(line);
	rl_clear_history();
	return (0);
}

