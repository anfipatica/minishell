#include "minishell.h"

void ft_pwd(void)
{

	char	*path;
	path = getcwd(NULL, 0);
	if (path)
	{
		printf("%s\n", path);
		free(path);
	}
}
