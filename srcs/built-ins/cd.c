#include "minishell.h"

void ft_cd(t_command *command)
{
	int	status;
	
	if (command->args->next == NULL)
	{
		status = chdir(ft_getenv("HOME", command->env, 0));
		if (status == CHDIR_ERROR)
			write(2, "cd: HOME not set\n", 18);
	}
	else
	{
		status = chdir(command->args->next->name);
		if (status == CHDIR_ERROR)
			perror(command->args->next->name);
	}

	while (command->env)
	{
		if (ft_strcmp("PWD", command->env->name) == 0)
		{
			free(command->env->value);
			command->env->value = getcwd(NULL, 0);
		}		
		command->env = command->env->next;
	}
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