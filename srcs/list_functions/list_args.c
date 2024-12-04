
#include "minishell.h"

/**
 * new_token creates a new token and allocates memory for it.
 */
t_args	*new_args(void)
{
	t_args	*new_args;

	new_args = (t_args *) malloc(sizeof(t_args));
	if (!new_args)
		return (NULL);
	new_args->arg = NULL;
	new_args->len_arg = 0;
	new_args->next = NULL;
	return (new_args);
}

/**
 * add_args_back receives the head of the list and the new args
 * to add at the end of said list. If there is no head, new becomes it.
 */
// void	add_args_back(t_args **lst, t_args *new)
// {
// 	t_args	*temp;

// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		new->next = NULL;
// 	}
// 	else
// 	{
// 		temp = *lst;
// 		while (temp->next)
// 			temp = temp->next;
// 		temp->next = new;
// 	}
// }

// void	ft_free_one_args(t_args *args)
// {
// 	if (!args)
// 		return ;
// 	free(args->path_args);
// 	//free_args matrix
// 	//free_redirect struct
// 	free(args);
// }

// /**
//  poi uscire * ft_free_argss frees the nodes of a list and the neccesary content
//  * inside each of them.
//  */
// void	ft_free_argss(t_args *args)
// {
// 	t_args	*temp;

// 	if (!args)
// 		return ;
// 	while (args != NULL)
// 	{
// 		temp = args->next;
// 		ft_free_one_args(args);
// 		args = temp;
// 	}
// }