#include "libft.h"

void	ft_lstiter_2nodes(t_list *lst, void (*function)(void *, void *))
{
	t_list	*temp;

	if (!lst || !function)
		return ;
	temp = lst;
	while (temp->next)
	{
		function(temp->content, temp->next->content);
		temp = temp->next;
	}
}