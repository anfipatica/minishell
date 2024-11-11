#include "../inc/minishell.h"


int	is_not_symbol(char c)
{

}

t_token	tokenizer(char **argv)
{
	int	i;
	int	j;

	i = -1;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j] && is_not_symbol(argv[i][j]))
			j++;
		create_token(ft_substr(argv[i], argv[i], j)); /////////////////////////////////
	}
}