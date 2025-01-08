
#include "minishell.h"

t_token *create_str_quote(char *start_quote, t_list *env)
{
	char	*finish_quote;
	int		length;

	finish_quote = ft_strchr(start_quote + 1, start_quote[0]);
	if (!finish_quote)
		return (NULL);
	length = ((finish_quote + 1) - start_quote);

// si antes de las comilla original tenemos ' ' entonces 
	if (start_quote[0] == '\"')
		return (expand_d_quote(start_quote, length, env));
	return (new_token(T_S_QUOTE, start_quote, length));
}
