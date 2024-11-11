#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef enum	s_token_value
{
	T_WORD,				// str
	T_REDIRECT_LEFT,	// <
	T_HERE_DOC,			// <<
	T_REDIRECT_RIGHT,	// >
	T_APPEND,			// >>
	T_PIPE,				// |
	// T_DOUBLE_QUOTE_STR,	//
	// T_SINGLE_QUOTE_STR,	//
	T_ENV,				// $
	T_SPACE				// ' '
}				t_token_value;

typedef struct s_token
{
//	int				index; //The index inside the list.
	t_token_value	type; //The token value.
	char			*str; //The actual text value -> La posicion en readline. Así no hay que hacer malloc
	int				length; // La longitud de str.
	struct s_token	*next; //A pointer to the next token.
}				t_token;

// Tokenizer.c

t_token	*tokenizer(char *line);

//history.c CAMBIAR NOMBRE

int		promptereitor(void);

//list.c

t_token	*new_token(t_token_value type, char *str, int length);
void	add_token_back(t_token **lst, t_token *new);
void	go_over_list(t_token *token);
void	ft_free_list(t_token *token);

#endif