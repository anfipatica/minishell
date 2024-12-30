
#include "minishell.h"

void twin_quote(char *line)
{

	int i = 0;
	char quote_type;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote_type = line[i];
			i++;
			while (line[i] != '\0' && line[i] != quote_type)
				i++;

		}
		if (line[i] == '\0')
			exit(22);
		i++;
	}
}

int	promptereitor(t_list *list_env)
{
	char		*line;
	t_list		*first_token;
//	t_list		*command;

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
			first_token = tokenizer(line, list_env);
			ft_lstiter(first_token, print_tokens);
			//list_checker(first_token);
			ft_lstiter(first_token, list_checker);

			// print_tokens(first_token);
			// command = automata(first_token);
			// ft_free_tokens(first_token);
			// ft_free_commands(command);
			ft_lstclear(&first_token, ft_free_one_token);
		}
		free(line);
	}
	free(line);
	rl_clear_history();
	return (0);
}

