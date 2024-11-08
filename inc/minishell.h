#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include "../libft/libft.h"

typedef enum	s_token_value
{
	STRING, // Any text.
	LESSER, // <
	GREATER, // >
	PIPE // |
}				t_token_value;

typedef struct s_token
{
	int				index; //The index inside the list.
	t_token_value	value; //The token value.
	char			*str; //The actual text value.
	struct s_token	*next; //A pointer to the next token.
}				t_token;

// Tokenizer.c

t_token	tokenizer(char **argv);

#endif