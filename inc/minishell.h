#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
 #include <unistd.h>
# include "libft.h"

# define SYMBOLS "<>|$- "

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define STD "\033[0m"
# define PURPLE "\033[0;35m"
# define BLUE "\033[1;36m"
# define ORANG "\033[1;33m"

//define automata
#define ERROR__STATE 4
#define ACCEPT_STATE 1
// typedef enum	s_token_value
// {
// 	T_WORD,				// str
// 	T_HERE_DOC,			// <<
// 	T_REDIRECT_LEFT,	// <
// 	T_APPEND,			// >>
// 	T_REDIRECT_RIGHT,	// >
// 	T_PIPE,				// |
// 	T_ENV,				// $
// 	T_SPACE,			// ' '
// 	T_FLAG,				// ? O -- (EN PRINCIPIO DEBERÍA SER PARTE DE T_WORD)
// 	T_D_QUOTE,	// ""
// 	T_S_QUOTE	// ''
// }				e_token_value;

typedef enum	s_token_value
{
	T_WORD,
	T_ENV,
	T_D_QUOTE,
	T_S_QUOTE,
	T_REDIRECT_LEFT,
	T_HERE_DOC,
	T_REDIRECT_RIGHT,
	T_APPEND,
	T_PIPE,
	T_FLAG,
	T_EXEC
}				e_token_value;

typedef struct s_token  
{
//	int				index;		// The index inside the list.
	e_token_value	type;		// The token value.
	char			*str;		// The actual text value -> La posicion en readline. Así no hay que hacer malloc
	char			*expanded;	 // string valor de la variable $ expandida
	int				length;		// La longitud de str.
	bool			free_expanded; // Si expanded hemos hecho malloc porque es propia o no porque viene de getenv.
	struct s_token	*next;		// A pointer to the next token.
	bool			is_exec;	// flag si T_WORD es executable.
}				t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_command
{

}				t_command;

// Tokenizer.c

t_token		*tokenizer(char *line, t_env *env);
int			wordeitor(t_token **head_token, char *start_word);
t_token		*token_chooser(char *line, t_env *env);
t_token		*symbol_tokenizer(e_token_value type, char *line, int n_symbol);


//promptereitor.c

void		twin_quote(char *line);
int			promptereitor(t_env *env);

//list_token.c

void		print_tokens(t_token *token);
t_token		*new_token(e_token_value type, char *str, int length);
void		add_token_back(t_token **lst, t_token *new);
void		ft_free_tokens(t_token *token);
void		ft_free_one_node(t_token *token);

//get_token_name.c

const char	*get_token_name(e_token_value token);

//list_env.c

void	print_env(t_env *env);
t_env	*new_env(char *name, char *value);
void	add_env_back(t_env **lst, t_env *new);
void	ft_free_env(t_env *env);

//expandetor.c

t_token		*expandetor(char *line, t_env *env);
t_token		*get_pid_expandetor();

// quoteitor.c

t_token	*expand_d_quote(char *start_quote, int length_dq, t_env *env);

// env.c

char	*ft_getenv(char *name, t_env *env, int length);
t_env	*create_node_env(char *line_env);
t_env	*copy_env(char **env);


// quotes_token_create.c

t_token	*create_str_quote(char *start_quote, t_env *env);

//freedom.c
void	freedom_error_fresh_token(t_token *head_token, char *line, t_env *env);

// quote_expandetor.c

char	*nothing_to_expand(int *n, char *str);
char	*maybe_expanded(int *n, char *str, t_env *env);
char	*get_pid_quote(void);

// automata.c

int	get_new_state(int current_state, int token);
int	print_states(t_token *token);

// list_checker.c

void	list_checker(t_token **list);

#endif