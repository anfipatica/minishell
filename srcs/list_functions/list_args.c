
#include "minishell.h"

size_t len_list_args(t_args *list)
{
	size_t i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char **lts_args_to_matrix(t_args *args)
{
	char	**args_matrix;
	int	i;

	if (!args)
		return (NULL);
	args_matrix = malloc((len_list_args(args) + 1) * sizeof(char *));
	if (!args_matrix)
		return(NULL);
	i = 0;
	while (args)
	{
		args_matrix[i] = args->name;
		i++;
		args = args->next;
	}
	args_matrix[i] = NULL;
/* 	for (int j = 0; args_matrix[j]; ++j)
		dprintf(2, "args_matrix = %s\n", args_matrix[j]); */
	return (args_matrix);
}

t_args	*new_args(char *arg)
{
	t_args	*new_args;

	new_args = (t_args *) malloc(sizeof(t_args));
	if (!new_args)
		return (NULL);
	new_args->name = arg;
	new_args->next = NULL;
	return (new_args);
}

/**
 * add_args_back receives the head of the list and the new args
 * to add at the end of said list. If there is no head, new becomes it.
 */
void	add_args_back(t_args **head, t_args *new)
{
	t_args	*temp;

	if (*head == NULL)
	{
		*head = new;
		new->next = NULL;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_free_one_args(t_args *args)
{
	if (!args)
		return ;

	free(args);
}

void	ft_free_list_args(t_args *arg_node)
{
	t_args	*temp;

	if (!arg_node)
	{
		return ;
	}
	while (arg_node)
	{
		temp = arg_node->next;
		ft_free_one_args(arg_node);
		arg_node = temp;
	}
}