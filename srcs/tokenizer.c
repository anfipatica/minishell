#include "../inc/minishell.h"

// TOKEN: | < << > >> $ WORD ' '


t_token	*tokenizer(char *line)
{
	t_token	*token;
	int		i;
	int		word_len;

	i = -1;
	word_len = 0;

	while (line[++i])
	{
		if (ft_strnstr(line + i, "<>|$", 1) != NULL)
		{
			//Ha encontrado un símbolo.

		}
		else if (ft_strnstr(line + i, "\"\'", 1) != NULL)
		{
			//Ha encontrado comillas.

		}
		else
		{
			//Es parte de un token word.
			word_len++;
			if (line[i + 1] == '\0')
			{
				token = new_token(T_WORD, &line[i - (word_len - 1)], word_len);
			}
		}
	}
	return (token);
}
