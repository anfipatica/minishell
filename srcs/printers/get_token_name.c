/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:16:26 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/03/04 15:16:28 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else if (token == T_D_QUOTE)
		return ("T_D_QUOTE");
	else if (token == T_S_QUOTE)
		return ("T_S_QUOTE");
	else if (token == T_IN_OUT)
		return ("T_IN_OUT");
	else if (token == T_SPACE)
		return ("T_SPACE");
	else
		return ("UNRECOGNIZED TOKEN");
}
