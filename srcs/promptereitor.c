
#include "minishell.h"

int	promptereitor(char **env)
{
	//(void)	env;
	char	*line;
	t_token	*first_token;
	//env = NULL;
	first_token = NULL;
	while (1)
	{
		line = readline("Prompt > ");
		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		if (line[0] != '\0')
		{
			//PRIMERO EXPANDIR!!!!!!!! Y LIMPIAR ESPACIOS!!!!!
			add_history(line);
			first_token = tokenizer(line, env);
			go_over_list(first_token);
			ft_free_list(first_token);
			free(line);
		}
	}
//	ft_free_list(first_token);
	free(line);
	rl_clear_history();
	return (0);
}

