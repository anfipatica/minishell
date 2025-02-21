#ifndef MINISHELL_H
# define MINISHELL_H


//!Definitions needed for signals to properly work in linux. Commented for mac.
# define _POSIX_C_SOURCE 199309L
# define _DEFAULT_SOURCE
/*
Antes en la minitalk tenia puesto esto
# define _POSIX_C_SOURCE 199309L
# define _DEFAULT_SOURCE

La cosa es que signal.h necesita tener __USE_POSIX definido para poder usar
sigaction, pero no podemos definir __USE_POSIX directamente, no sé muy bien por
qué pero lo que es cierto es que features.h, la librería que incluye signal.h,
lo primero que hace es undef __USE_POSIX por lo que aunque nosotros la definamos,
no sirve.
La parte de features.h que vuelve a definir __USE_POSIX tiene una serie de
condiciones:

#if (defined _POSIX_SOURCE					\
     || (defined _POSIX_C_SOURCE && _POSIX_C_SOURCE >= 1)	\
     || defined _XOPEN_SOURCE)
# define __USE_POSIX	1
#endif

Por tanto, con definir _POSIX_SOURCE nos vale. De hecho el propio manual de
sigaction dice:

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       sigaction(): _POSIX_C_SOURCE

       siginfo_t: _POSIX_C_SOURCE >= 199309L

Por tanto imagino que por eso puse lo otro, pero en principio parece funcionar
igual ?? no sé ya veremos xD
*/

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stddef.h>
# include <errno.h>
# include <signal.h>
# include "libft.h"

//# define SYMBOLS "<>|$- "

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define STD "\033[0m"
# define PURPLE "\033[0;35m"
# define BLUE "\033[1;36m"
# define ORANG "\033[1;33m"

//define automata
# define ERROR__STATE	5
# define ACCEPT_STATES	2
# define PIPE_STATE		4

# define	ARGS	0
# define	ENV	1

//ERRORS
# define OK 0
# define IS_DIR 1
# define COMMAND_NOT_FOUND 2
# define INVALID_EXPORT_IDENTIFIER 3
# define OPEN_ERROR -1
# define CD_ERROR 1
# define CHDIR_ERROR -1

# define O_REDIRECT_RIGHT (O_WRONLY | O_CREAT | O_TRUNC)
# define O_REDIRECT_APPEND (O_WRONLY | O_CREAT | O_APPEND)
# define O_HERE_DOC (O_RDONLY)
# define O_REDIRECT_LEFT (O_RDONLY)

# define STD_PERMISSIONS 0644
# define NULL_FD -2

# define SPACES " \f\n\r\t\v"
# define QUOTES "\"\'"
# define SYMBOLS "|<>"

# define OUT_FILE 1
# define IN_FILE 0

// EXEC
# define CHILD 0

//EXIT_STATUS
# define SIGINT_SIGNAL 130

extern unsigned char	g_exit_status;

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
// 	T_D_QUOTE,			// ""
// 	T_S_QUOTE			// ''
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
	char				*name; //arg del rispectivo redirect
	e_token_value		redirect_type;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_args
{
	char			*name;
	struct s_args	*next;
}				t_args;

typedef struct s_command
{
	// int				p_fds[2]; awhawhwahawhawhaw
	char				*path_command;
	t_args				*args;
	t_redirect			*head_redirect; //?Quizás normalizar más estos nombres, que uno sea head y otro solo args me da un poco de toc
	t_env				*env;
	struct s_command	*next;		// A pointer to the next token.

}				t_command;

typedef struct s_backpack
{
	t_command	*head_command;
	t_command	*last_command;
	t_args		*arg_aux;
	t_redirect	*redirect_aux;
	t_token		*token;
	t_env		*env;
}					t_backpack;

// typedef struct s_error_return
// {
// 	int	error_return[1];
// }				t_error_return;

/* ----------- LIST_FUNCTIONS ----------- */
//list_command.c

void		ft_free_commands(t_command *command);
void		ft_free_one_command(t_command *command);
void		add_command_back(t_command **lst, t_command *new);
t_command	*new_command(t_env *env);
void len_command_list(t_command *command);

//list_token.c

t_token		*new_token(e_token_value type, char *str, int length);
void		add_token_back(t_token **lst, t_token *new);
void		ft_free_tokens(t_token *token);
void		ft_free_one_node(t_token *token);
t_token	*check_and_delete_space(t_token *lst);
t_token	*check_and_delete_env(t_token *lst, t_token *lst_prev);

// list_env.c

char	*ft_getenv(char *name, t_env *env, int length);
t_env	*create_node_env(char *line_env);
t_env	*copy_env(char **env);
char	**lts_env_to_matrix(t_env *env);
void	ft_free_env(t_env *env);
void	ft_free_one_env(t_env *env);

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
void	print_tokens(t_token *token);
void print_commands(t_command *command);


//get_token_name.c

const char	*get_token_name(e_token_value token);
int		openeitor(int *p_fds, const char *file, int flags, mode_t mode);
void	child_pepa_new(t_command *command, int	action, int	p_fds[2]);


/* ----------- EVERYTHING ELSE ---------- */

// Tokenizer.c

t_token		*tokenizer(char *line, t_env *env);
int			wordeitor(t_token **head_token, char *start_word);
t_token		*token_chooser(char *line, t_env *env);
t_token		*symbol_tokenizer(e_token_value type, char *line, int n_symbol);

// promptereitor.c

bool		twin_quote(char *line);
int			promptereitor(t_env *env);

// list_env.c

void	print_env(t_env *env);
t_env	*new_env(char *name, char *value);
void	add_env_back(t_env **lst, t_env *new);
void	ft_free_env(t_env *env);

// expandetor.c

t_token		*expandetor(char *line, t_env *env);
char			*get_char_pid();
t_token		*get_pid_expandetor();

// quoteitor.c

t_token	*expand_d_quote(char *start_quote, int length_dq, t_env *env);

// quotes_token_create.c

t_token	*create_str_quote(char *start_quote, t_env *env);

// freedom.c

void	freedom_error_fresh_token(t_token *head_token, char *line, t_env *env);
void	free_exit_execution(char *path_name, char **matrix[2]);

// quote_expandetor.c

char	*nothing_to_expand(int *n, char *str);
char	*maybe_expanded(int *n, char *str, t_env *env);
char	*get_pid_quote(void);

// automata.c

int	get_new_state(int current_state, int token);
t_command	*automata(t_token *token, t_env *env);

// automata_func.c

int	insert_command(t_backpack *backpack);
int	insert_args(t_backpack *s_backpack);
int	set_redirect_type(t_backpack *backpack);
int	insert_file(t_backpack *backpack);
int	end_command(t_backpack *backpack);
int	syntax_error(t_backpack *backpack);

// list_checker.c

void	list_checker(t_token **list);

// executor.c
int		daddy_executor(t_command *command);
void	begin_execution(t_command *command);
void	execute_or_error(char **matrix[2], char *path_name);


// built-ins
void	ft_cd(t_command *command);
void 	ft_echo(t_command *command);
void 	ft_env(t_command *command);
void 	ft_exit(t_command *command);
int		ft_export(t_command *command);
bool	valid_var_name(char	*name);

void 	ft_pwd(void);
void 	ft_unset(t_command *command);

// error.c
void	error_exit(char *str, int error);
void	ft_perror(char *str);
void	print_error(char *str, int error);

// here_docereitor.c
char	*filename_generator(void);
char	*here_dokeitor(char *limiter, char *new_temp_file);
void	find_heredoc(t_command *file);

//fd_handler.c

int	handle_files(t_redirect *file);
int	dup2_openeitor(char *file, int flags, mode_t mode, int system_fd);

//check_builtins.c

int	check_builtins(t_command *command);
bool	exec_builtin(t_command *command);

//signals.c
void	child_signal_handler(int signal);
void	father_signal_handler(int signal);
void	heredoc_signal_handler(int signal);

//commander.c
char	*find_path_name(char *cmd, char **envp, char **cmd_arg);


#endif
