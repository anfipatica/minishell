#include "minishell.h"

const char	*get_token_name(t_token_value token)
{
	if (token == T_WORD)
		return ("T_WORD");
	else if (token == T_HERE_DOC)
		return ("T_HERE_DOC");
	else if (token == T_REDIRECT_LEFT)
		return ("T_REDIRECT_LEFT");
	else if (token == T_APPEND)
		return ("T_APPEND");
	else if (token == T_REDIRECT_RIGHT)
		return ("T_REDIRECT_RIGHT");
	else if (token == T_PIPE)
		return ("T_PIPE");
	else if (token == T_ENV)
		return ("T_ENV");
	else if (token == T_SPACE)
		return ("T_SPACE");
	else if (token == T_FLAG)
		return ("T_FLAG");
	else if (token == T_DOUBLE_QUOTE_STR)
		return ("T_DOUBLE_QUOTE_STR");
	else if (token == T_SINGLE_QUOTE_STR)
		return ("T_SINGLE_QUOTE_STR");
	return ("UNKNOWN_TOKEN");
}
