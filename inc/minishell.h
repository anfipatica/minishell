#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
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
	T_D_QUOTE,	// ""
	T_S_QUOTE	// ''
}				t_token_value;

typedef struct s_token  
{
//	int				index;		// The index inside the list.
	t_token_value	type;		// The token value.
	char			*str;		// The actual text value -> La posicion en readline. Así no hay que hacer malloc
	char			*expanded;	 // string valor de la variable $ expandida
	int				length;		// La longitud de str.
	bool			free_expanded; // Si expanded hemos hecho malloc porque es propia o no porque viene de getenv.
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

//expandetor.c

t_token		*expandetor(char *line);
t_token	*get_pid_expandetor(void);

// quoteitor.c

void	is_closed_quote(char *line);
void	is_even_quote(char *line);

#endif