
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

int	promptereitor(t_env *env)
{
	char		*line;
	t_token		*first_token;
	t_command	*command;

	first_token = NULL;
	int i = 0;
	while (1)
	{
		printf("iteration: %d\n", i);
		line = readline("Prompt > ");
		twin_quote(line);
		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			first_token = tokenizer(line, env);
			print_tokens(first_token);
			list_checker(&first_token);
			print_tokens(first_token);
			command = automata(first_token, env);
			print_commands(command);
			ft_free_commands(command);
			ft_free_tokens(first_token);

		}
		free(line);
		i++;
	}
	free(line);
	rl_clear_history();
	return (0);
}

