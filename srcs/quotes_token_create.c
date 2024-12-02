
#include "minishell.h"

t_token *create_str_quote(char *start_quote, t_env *env)
{
	char	*finish_quote;
	int		length;

	finish_quote = ft_strchr(start_quote + 1, start_quote[0]);
	if (!finish_quote)
		return (NULL);
	length = ((finish_quote + 1) - start_quote);
		//TODO "hola""""""""""""que_tal -> "holaque tal"
		//? "$A"'hola' -> echohola
		//? '$A'"hola" -> $Ahola
	if (start_quote[0] == '\"')
		return (expand_d_quote(start_quote, length, env));
	return (new_token(T_S_QUOTE, start_quote, length));
}
