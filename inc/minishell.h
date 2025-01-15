#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stddef.h>
# include <errno.h>
# include "libft.h"

# define SYMBOLS "<>|$- "

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define STD "\033[0m"
# define PURPLE "\033[0;35m"
# define BLUE "\033[1;36m"
# define ORANG "\033[1;33m"

//define automata
#define ERROR__STATE	5
#define ACCEPT_STATES	2

#define	ARGS	0
#define	ENV	1

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
//	int				index;		// The index inside the list.
	e_token_value	type;		// The token value.
	char			*str;		// The actual text value -> La posicion en readline. Así no hay que hacer malloc
	char			*expanded;	 // string valor de la variable $ expandida
	int				length;		// La longitud de str.
	bool			free_expanded; // Si expanded hemos hecho malloc porque es propia o no porque viene de getenv.
	bool			is_exec;	// flag si T_WORD es executable.
	struct s_token	*next;		// A pointer to the next token.
}				t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_redirect
{
	char				*name;
	e_token_value		redirect_type;
	struct s_redirect	*next; 
}				t_redirect;

typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
}				t_args;

typedef struct s_command
{
	int				p_fds[2];
	char				*path_command;
	t_args				*args;
	t_redirect			*redirect;
	t_redirect			*aux_redirect;
	t_env				*env;
	struct s_command	*next;		// A pointer to the next token.

}				t_command;


/* ----------- LIST_FUNCTIONS ----------- */
//list_command.c

void		ft_free_commands(t_command *command);
void		ft_free_one_command(t_command *command);
void		add_command_back(t_command **lst, t_command *new);
t_command	*new_command(t_env *env);

//list_token.c

t_token		*new_token(e_token_value type, char *str, int length);
void		add_token_back(t_token **lst, t_token *new);
void		ft_free_tokens(t_token *token);
void		ft_free_one_node(t_token *token);
t_token *eval(t_token *lst);

// list_env.c

char	*ft_getenv(char *name, t_env *env, int length);
t_env	*create_node_env(char *line_env);
t_env	*copy_env(char **env);
char	**lts_env_to_matrix(t_env *env);

// list_args.c

t_args	*new_args(char *arg);
void	add_args_back(t_args **head, t_args *new);
void	ft_free_one_args(t_args *args);
void	ft_free_list_args(t_args *arg_node);
char	**lts_args_to_matrix(t_args *args);

// list_redirect.c
t_redirect	*new_redirect(e_token_value redirect_type);
void	add_redirect_back(t_redirect **lst, t_redirect *new);
void	ft_free_one_redirect(t_redirect *redirect);
void	ft_free_redirects(t_redirect *redirect);

/* -------------- PRINTERS ------------- -*/

//get_token_name.c

const char	*get_token_name(e_token_value token);

//printers.c

void	print_commands(t_command *command);
void		print_tokens(t_token *token);
int	print_states(t_token *token);


/* --------------- PEPEX ---------------- */

char	*find_path_name(char *cmd, char **env, char **cmd_arg);
void	child_pepe_first(int *p_fds, char *first_cmd, char *in_f, char **envp);
void	child_pepa_midle(int *p_fds, int aux_fd_r, char *argv, char **envp);
pid_t	child_paolo_last(int *p_fds, char **argv, int argc, char **envp);
void	print_error(const char *msg);
char	*here_dokeitor(char *limiter);
void	ft_perror(char *str);


/* ----------- EVERYTHING ELSE ---------- */

// Tokenizer.c

t_token		*tokenizer(char *line, t_env *env);
int			wordeitor(t_token **head_token, char *start_word);
t_token		*token_chooser(char *line, t_env *env);
t_token		*symbol_tokenizer(e_token_value type, char *line, int n_symbol);

//promptereitor.c

void		twin_quote(char *line);
int			promptereitor(t_env *env);

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
t_command	*automata(t_token *token, t_env *env);

// automata_func.c

int	insert_command(t_token	*token, t_command *command);
int	insert_args(t_token	*token, t_command *command);
int	set_redirect_type(t_token	*token, t_command *command);
int	insert_file(t_token	*token, t_command *command);
int	end_command(t_token	*token, t_command *command);
int	sintax_error(t_token	*token, t_command *command);

// list_checker.c

void	list_checker(t_token **list);

//EXECUTOR.C
int	executor(t_command *command);


#endif
