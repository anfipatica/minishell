#include "minishell.h"

void ft_pwd(void)
{
	printf("FT_PWD\n");
	char	*path;
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}
