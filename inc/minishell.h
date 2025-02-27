/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:28:05 by ymunoz-m          #+#    #+#             */
/*   Updated: 2025/02/28 00:51:03 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Definitions needed for signals to properly work in linux. Commented for mac.
# define _POSIX_C_SOURCE 199309L
# define _DEFAULT_SOURCE

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
# include "defines.h"
# include "structs.h"

extern unsigned char	g_exit_status;

/* ----------- LIST_FUNCTIONS ----------- */
//list_command.c

t_command	*new_command(t_env *env, t_token *token);
void		add_command_back(t_command **lst, t_command *new);
void		ft_free_commands(t_command *command);
void		ft_free_one_command(t_command *command);

//list_token.c

t_token		*new_token(t_token_value type, char *str, int length);
void		add_token_back(t_token **lst, t_token *new);
void		ft_free_tokens(t_token *token);
void		ft_free_one_node(t_token *token);
t_token		*check_and_delete_space(t_token *lst);
t_token		*check_and_delete_env(t_token *lst, t_token *lst_prev);

// list_env.c

char		*ft_getenv(char *name, t_env *env, int length);
t_env		*create_node_env(char *line_env);
t_env		*copy_env(char **env);
char		**lts_env_to_matrix(t_env *env);

// list_env_free.c

void		ft_free_env(t_env *env);
void		ft_free_one_env(t_env *env);

// list_args.c

size_t		len_list_args(t_args *list);
char		**lts_args_to_matrix(t_args *args);
t_args		*new_args(char *arg);
void		add_args_back(t_args **head, t_args *new);

// lis_args_free.c

void		ft_free_one_args(t_args *args);
void		ft_free_list_args(t_args *arg_node);

// list_redirect.c
t_redirect	*new_redirect(t_token_value redirect_type);
void		add_redirect_back(t_redirect **lst, t_redirect *new);
void		ft_free_one_redirect(t_redirect *redirect);
void		ft_free_redirects(t_redirect *redirect);

/* ----------- BUILTINS ----------- */

void		ft_cd(t_command *command);
void		ft_echo(t_command *command);
void		ft_env(t_command *command);
void		ft_exit(t_command *command);
int			ft_export(t_command *command);
bool		valid_var_name(char	*name);
void		kermit(void);
void		ft_pwd(t_env *env);
void		ft_unset(t_command *command);

/* ----------- EVERYTHING ELSE ---------- */

// Tokenizer.c

t_token		*tokenizer(char *line, t_env *env);
int			wordeitor(t_token **head_token, char *start_word);
t_token		*token_chooser(char *line, t_env *env);
t_token		*symbol_tokenizer(t_token_value type, char *line, int n_symbol);

// heredoc_tokenizer.c

t_token		*handle_heredoc_limiter(char *line, t_env *env);
int			find_valid_delimitor(char *line);

// promptereitor.c

bool		twin_quote(char *line);
int			promptereitor(t_env *env);

// list_env.c

void		print_env(t_env *env);
t_env		*new_env(char *name, char *value);
void		add_env_back(t_env **lst, t_env *new);
void		ft_free_env(t_env *env);

// expandetor.c

t_token		*expandetor(char *line, t_env *env);
char		*get_char_pid(void);
t_token		*get_pid_expandetor(void);

// quoteitor.c

t_token		*expand_d_quote(char *start_quote, int length_dq, t_env *env);

// quotes_token_create.c

t_token		*create_str_quote(char *start_quote, t_env *env);

// freedom.c

void		freedom_error_fresh_token(t_token *token, char *line, t_env *env);
void		free_exit_execution(char *path_name, char **matrix[2]);
void		free_all(t_command *command);

// quote_expandetor.c

char		*nothing_to_expand(int *n, char *str);
char		*maybe_expanded(int *n, char *str, t_env *env);
char		*get_pid_quote(void);

// automata.c

int			get_new_state(int current_state, int token);
t_command	*automata(t_token *token, t_env *env);

// automata_func.c

int			insert_command(t_backpack *backpack);
int			insert_args(t_backpack *s_backpack);
int			set_redirect_type(t_backpack *backpack);
int			insert_file(t_backpack *backpack);
int			end_command(t_backpack *backpack);
int			syntax_error(t_backpack *backpack);

// list_checker.c

void		list_checker(t_token **list);

// list_checker_utils.c

void		turn_to_word(t_token *token);
void		unlink_node(t_token **before_space);
void		join_tokens(t_token *node1, t_token *node2);

// executor.c

int			daddy_executor(t_command *command);
void		begin_execution(t_command *command);
void		execute_or_error(char **matrix[2], char *path, t_command *command);

// executor_utils.c

void		restore_builtin_fds(int aux_stdout, int aux_stdin);
void		restore_daddy_fds(bool multiple_commands, int in_fd, int *pipefd);
void		matrix_filler(t_command *command, char ***matrix);

//executor_jr.c

void		exec_jr_fd_handler(t_command *command, int in_fd, int *pipefd);
void		exec_jr(t_command *command, int in_fd, int *pipefd);

//executor_dad.c

int			daddy_executor(t_command *command);
void		wait_all(void);


// error.c
void		error_exit(char *str, int error, t_command *command);
void		ft_perror(char *str);
void		print_error(char *str, int error);

// here_docereitor.c

void		write_heredoc_expanded(char *line, int heredoc_fd, t_env *env);
char		*here_dokeitor(char *eof, char *n_t_f, int *status, t_env *env);
int			find_heredoc(t_command *command);
void		while_write_heredoc(char *eof, char *eof_aux, int h_fd, t_env *env);

// here_dokeitor_utils.c

char		*filename_generator(void);
int			heredoc_father(int heredoc_fd);
char		*ft_clean_delimiter(char *delimiter);

//fd_handler.c

int			handle_files(t_redirect *file);
int			dup2_openeitor(char *file, int flags, mode_t mode, int system_fd);

//check_builtins.c

int			check_builtins(t_command *command);
bool		exec_builtin(t_command *command);

//signals.c
void		child_signal_handler(int signal);
void		father_signal_handler(int signal);
void		heredoc_signal_handler(int signal);
void		sigquit_signal_handler(int signal);

//commander.c
char		*find_path_name(char *cmd, char **envp, char **cmd_arg);

#endif
