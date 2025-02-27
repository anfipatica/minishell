
#include "minishell.h"

bool twin_quote(char *line)
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
		{
			printf(RED"Hey,\n"
			"your quote is missing a buddy to complete the pair!\n"
			"Don’t leave it hanging, it’s lonely!\n"STD);
			free(line);
			return (false);
		}
		i++;
	}
	return (true);
}

int	promptereitor(t_env *env)
{
	char		*line;
	t_token		*first_token;
	t_command	*command;

	while (1)
	{
		signal(SIGINT, father_signal_handler);
		line = readline("prompt > ");
		if (!line || ft_strncmp(line, "exit", 5) == 0)  // ! hacer ft_EXIT
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			if (twin_quote(line) == false)
				continue ;
// 
			first_token = tokenizer(line, env);
			//print_tokens(first_token);
			list_checker(&first_token);
			//print_tokens(first_token);
			command = automata(first_token, env);
			//print_commands(command);
			if (command)
				begin_execution(command);
			if (command)
				ft_free_commands(command);
			ft_free_tokens(first_token);
			//printf("g_exit_status = %d\n", g_exit_status);
		}
		free(line);
	}
	free(line);
	rl_clear_history();
	return (0);
}
