#include "minishell.h"

void ft_cd(t_command *command)
{
	int	status;

	printf("holaaaaa\n"); 
	
	if (command->args->next == NULL)
	{
		status = chdir(ft_getenv("HOME", command->env, 0));
		if (status == CHDIR_ERROR)
			printf("bash: cd: HOME not set\n");
	}
	else
		status = chdir(command->args->next->name);
	
	if (status == CHDIR_ERROR)
		g_exit_status = CD_ERROR;
	else
		g_exit_status = OK;
}

//d: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory

// int chdir(const char *path);
// char *getcwd(char *buf, size_t size);
// struct dirent *readdir(DIR *dirp);
// int closedir(DIR *dirp);