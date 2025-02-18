#include "minishell.h"
/* 
	printf("position_of_igual: %lu\n", position_of_igual);
	printf("str_with_igual + 1: %lu\n", str_with_igual);
	printf("position_of_igual - str_with_igual + 1: %lu\n", position_of_igual - str_with_igual + 1); */

void ft_export(t_command *command)
{
	t_env	*aux_list;
	char	*name;
	char	*value;
	char	*str_with_igual;
	char	*position_of_igual;
	
	aux_list = command->env;
	str_with_igual = command->args->next->name;
	position_of_igual = ft_strchr(str_with_igual, '=');
	name = ft_substr(str_with_igual, 0, position_of_igual - str_with_igual);
	value = ft_substr(str_with_igual, position_of_igual - str_with_igual + 1, ft_strlen(position_of_igual + 1));
	while (command->env)
	{
		if (ft_strcmp(command->env->name, name) == 0)
		{
			free(command->env->value);
			free(name);
			command->env->value = value;
			return ;
		}
		command->env = command->env->next;
	}
	command->env = aux_list;
	add_env_back(&command->env, new_env(name, value));
}
