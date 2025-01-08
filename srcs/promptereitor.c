
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

bool	predicate_if_space_or_empty(void *content, void *context)
{
	printf("content = %p\n", content);
	if (content == NULL)
	{
		printf("asdasdasd\n");
		return (true);
	}
	if (ft_strcmp((const char *)context, ((t_token *)content)->str) == 0)
		return (true);
	return (false);
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
			first_token = tokenizer(line, env);
			print_tokens(first_token);
			list_checker(&first_token);
			print_tokens(first_token);
			command = automata(first_token);
			//print_states(first_token);
			ft_free_tokens(first_token);
			ft_free_commands(command);
		}
		free(line);
	}
	free(line);
	rl_clear_history();
	return (0);
}

