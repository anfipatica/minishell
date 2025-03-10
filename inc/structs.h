/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:30:59 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/03/05 17:05:47 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_token_value
{
	T_WORD,
	T_ENV,
	T_REDIRECT_LEFT,
	T_HERE_DOC,
	T_REDIRECT_RIGHT,
	T_APPEND,
	T_IN_OUT,
	T_PIPE,
	T_SPACE,
	T_S_QUOTE,
	T_D_QUOTE
}				t_token_value;

typedef struct s_token
{
	t_token_value	type;
	char			*str;
	char			*expanded;
	int				length;
	bool			free_expanded;
	bool			is_exec;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_redirect
{
	char				*name;
	t_token_value		redirect_type;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_args
{
	char			*name;
	struct s_args	*next;
}				t_args;

typedef struct s_command
{
	char				***execve_matrix;
	char				*path_command;
	t_args				*args;
	t_redirect			*head_redirect;
	t_token				*token_pointer;
	t_env				*env;
	char				*line;
	struct s_command	*next;

}				t_command;

typedef struct s_backpack
{
	t_command	*head_command;
	t_command	*last_command;
	t_args		*arg_aux;
	t_redirect	*redirect_aux;
	t_token		*head_token;
	t_token		*token;
	t_env		*env;
}					t_backpack;
