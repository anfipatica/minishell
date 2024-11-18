#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft.h"

# define SYMBOLS "<>|$- "

typedef enum	s_token_value
{
	T_WORD,				// str
	T_HERE_DOC,			// <<
	T_REDIRECT_LEFT,	// <
	T_APPEND,			// >>
	T_REDIRECT_RIGHT,	// >
	T_PIPE,				// |
	T_ENV,				// $
	T_SPACE,			// ' '
	T_FLAG,				// - O --
	T_DOUBLE_QUOTE_STR,	// ""
	T_SINGLE_QUOTE_STR	// ''
}				t_token_value;

typedef struct s_token  
{
//	int				index;		// The index inside the list.
	t_token_value	type;		// The token value.
	char			*str;		// The actual text value -> La posicion en readline. Así no hay que hacer malloc
	char			*expanded;	// string valor de la variable $ expandida
	int				flags[2];	// flag para ver si tiene que expandir	
	int				length;		// La longitud de str.
	struct s_token	*next;		// A pointer to the next token.
}				t_token;

typedef struct s_command
{

}				t_command;

// Tokenizer.c

t_token	*tokenizer(char *line, char **env);

//history.c CAMBIAR NOMBRE

int		promptereitor(char **env);

//list.c

t_token		*new_token(t_token_value type, char *str, int length);
void		add_token_back(t_token **lst, t_token *new);
void		go_over_list(t_token *token);
void		ft_free_list(t_token *token);
const char	*get_token_name(t_token_value token);
t_token		*expandetor(char *line);


#endif