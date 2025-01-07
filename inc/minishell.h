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
#define ERROR__STATE	6
#define ACCEPT_STATES	3

// typedef enum	s_token_value
// {
// 	T_WORD,				// str
// 	T_SPACE,			// ' '
// 	T_HERE_DOC,			// <<
// 	T_REDIRECT_LEFT,	// <
// 	T_APPEND,			// >>
// 	T_REDIRECT_RIGHT,	// >
// 	T_PIPE,				// |
// 	T_ENV,				// $
// 	T_FLAG,				// ? O -- (EN PRINCIPIO DEBERÍA SER PARTE DE T_WORD)
// 	T_D_QUOTE,	// ""
// 	T_S_QUOTE	// ''
// }				e_token_value;

typedef enum	s_token_value
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
}				e_token_value;

typedef struct s_token  
{
	int				index;		// The index inside the list.
	e_token_value	type;		// The token value.
	char			*str;		// The actual text value -> La posicion en readline. Así no hay que hacer malloc
	char			*expanded;	 // string valor de la variable $ expandida
	int				length;		// La longitud de str.
	bool			free_expanded; // Si expanded hemos hecho malloc porque es propia o no porque viene de getenv.
//	int				i_printer;
	//bool			is_exec;	// flag si T_WORD es executable.
}				t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
}				t_env;

typedef struct	s_redirect
{
	char				*name;
	e_token_value		redirect_type;
}				t_redirect;

typedef struct s_command
{
	char				*path_command;
	char				**args;
	t_redirect			*redirect;
}				t_command;

typedef struct s_args
{
	char			*arg;
	int				len_arg;
}				t_args;

typedef	struct	s_printers
{
	int			i;
}				t_printers;


/* ----------- LIST_FUNCTIONS -----------*/
//list_command.c

void		ft_free_commands(t_command *command);
void		ft_free_one_command(t_command *command);
void		add_command_back(t_command **lst, t_command *new);
t_command	*new_command(void);

//list_token.c

void		print_tokens(void *token);
t_token		*new_token(e_token_value type, char *str, int length);
void		ft_free_one_token(void **token);

// list_env.c

char	*ft_getenv(char *name, t_list *env, int length);
t_env	*create_node_env(char *line_env);
t_list	*copy_env(char **env);

// list_args.c

t_args	*new_args(void);
// char	*ft_getenv(char *name, t_env *env, int length);
// t_env	*create_node_env(char *line_env);
// t_env	*copy_env(char **env);



// Tokenizer.c

t_list		*tokenizer(char *line, t_list *env);
int			wordeitor(t_list **head_token, char *start_word);
t_token		*token_chooser(char *line, t_list *env);
t_token		*symbol_tokenizer(e_token_value type, char *line, int n_symbol);


//promptereitor.c

void		twin_quote(char *line);
int			promptereitor(t_list *env);


//get_token_name.c

const char	*get_token_name(e_token_value token);

//list_env.c

void	print_env(t_env *env);
t_env	*new_env(char *name, char *value);
void	ft_free_env(void *env);

//expandetor.c

t_token		*expandetor(char *line, t_list *env);
t_token		*get_pid_expandetor();

// quoteitor.c

t_token *expand_d_quote(char *start_quote, int length_dq, t_list *env);
void if_is_dollar(char **expanded, char *line_after_dollar, int *i, t_list *env);

// quotes_token_create.c

t_token	*create_str_quote(char *start_quote, t_list *env);

//freedom.c
void	freedom_error_fresh_token(t_list *head_token, char *line, t_list *env);

// quote_expandetor.c

char	*nothing_to_expand(int *n, char *str);
char	*maybe_expanded(int *n, char *str, t_list *env);
char	*get_pid_quote(void);

// automata.c

int	get_new_state(int current_state, int token);
t_command	*automata(t_token *token);
int	print_states(t_token *token);

// automata_func.c
int	insert_command(t_token	*token, t_command *command);
int	insert_flag(t_token	*token, t_command *command);
int	set_redirect_type(t_token	*token, t_command *command);
int	insert_file(t_token	*token, t_command *command);
int	end_command(t_token	*token, t_command *command);
int	sintax_error(t_token	*token, t_command *command);


// list_checker.c

void	list_checker(void *node1, void *node2);

#endif