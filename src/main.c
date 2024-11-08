#include "../inc/minishell.h"

int	main(int argc, char **argv)
{
	t_token token;
	if (argc == 1)
		return (1);
	for (int i = 0; argv[i]; i++)
		printf("argv[%d] =  %s\n", i, argv[i]);
	token = tokenizer(argv);
	return (0);
}