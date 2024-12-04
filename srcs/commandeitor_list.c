#include "minishell.h"

char	*find_path_name_ms(char *cmd, t_env **env, t_args *cmd_arg)
{
	char	**all_path;
	char	*path_name;
	int		i;

	if (cmd == NULL || ft_strchr(cmd, '/') != NULL)
		return (cmd);
	i = 0;
	while (env != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			all_path = ft_split(envp[i] + 5, ':');
			if (all_path == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	path_name = check_path(all_path, cmd);
	error_path(path_name, cmd, all_path, cmd_arg);
	free_double_pointer(all_path);
	return (path_name);
}

t_command commandeitor_list(t_token *list, t_env *env)
{
	t_command *new_list;
	
	new_list = new_command();
	while (list)
	{
		if (list->type == T_WORD)
			new_list->path_command = path_creator(list, env);
		else
			new_list->redirect = new_redirect(list->type);

		
		list = list->next;
	}
}

char *path_creator(t_token *list, t_env *env)
{
	char	*first_word;

	if (!list->expanded)
		first_word = list->str;
	else
		first_word = list->expanded;
	find_path_name_ms(first_word env);
}