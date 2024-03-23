/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:47:43 by mott              #+#    #+#             */
/*   Updated: 2024/03/04 15:23:26 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
// # include "builtin.h"

// printf, perror
#include <stdio.h>

// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
#include <readline/readline.h>

// add_history
#include <readline/history.h>

// malloc, free, exit, getenv
#include <stdlib.h>

// write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2,
// pipe, isatty, ttyname, ttyslot
#include <unistd.h>

// open
#include <fcntl.h>

// wait, waitpid, wait3, wait4
#include <sys/wait.h>

// signal, sigaction, sigemptyset, sigaddset, kill
#include <signal.h>

// stat, lstat, fstat
#include <sys/stat.h>

// opendir, readdir, closedir
#include <dirent.h>

// strerror
#include <string.h>

// ioctl
#include <sys/ioctl.h>

// tcsetattr, tcgetattr
#include <termios.h>

// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <curses.h>
#include <term.h>

#include <stdbool.h>
#include <errno.h>

# define PROMPT_STD "$ "
# define PROMPT_MULTI_LINE "> "

typedef enum	e_token_type
{
	UNKNOWN,
	COMMAND,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIR_IN,
	REDIR_HEREDOC,
	REDIR_OUT,
	REDIR_APPEND,
	PIPE,
	DOLLAR,
	DQMARK,
	AND,
	OR,
	PARENTHESIS_L,
	PARENTHESIS_R,
	WILDCARD
}	t_type;

typedef struct	s_token
{
	t_type	type;
	char			*content;
	int				length;
	struct s_token	*next;
}	t_token;

typedef struct	s_ast
{
	t_type	type;
	char			**argv;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_exec
{
	int	fd_stdin;
	int	fd_stdout;
	int	exit_status;
}	t_exec;

// minishell.c
int				main(int argc, char **argv, char **envp);
void			read_eval_print_loop(t_env *env);

// LEXER
t_token			*tokenizer(char *user_input, t_env *env, t_exec *exec);
int				set_token_length(char *user_input);
t_type			set_type(char	*content, int token_length);
void			expand_token(t_token *token, t_env *env, t_exec *exec);
void			proccess_commands(t_token *token, t_env *env);
char			*expand_dollar_sign(const char *content, t_env *env);
char			*expand_dollar_qmark(t_exec *exec);
char			*expand_double_quote(const char *content, t_env *env);
char			*expand_wildcard(char *content);
int				match_wildcard(char *pattern, char *str);
void			wildcard_path_to_token(char *path, t_token **current);
char			*remove_double_quotes(const char *content);
char			*remove_single_quotes(const char *content);
char			*get_quote_start(char *str);
char 			*get_quote_end(char *str, char quote_type);
// token_ops
t_token			*token_new(void);
t_token			*token_last(t_token *token);
void			token_add_back(t_token **token, t_token *new_token);
int				tokens_size(t_token *tokens);

// PARSER
t_ast			*ast_parser(t_token **token);
t_ast			*ast_cmd(t_token **token);
t_ast			*ast_redirect(t_token **token, t_ast *cmd_node);
t_ast			*ast_pipe(t_token **token, t_ast *left);
t_ast			*ast_logical(t_token **token, t_ast *left);
t_ast			*ast_parenthesis(t_token **token);
t_ast			*new_ast_node(t_token *token);
char			**token_to_str_array(t_token *tokens);
int				count_command_group(t_token *tokens);
bool			is_redirect(t_type type);
bool			is_logical(t_type type);
void			print_ast(t_ast* node, int level);
// EXECUTOR
// exec_main
int				exec_main(t_ast *ast_head, t_env *env, t_exec *exec);
bool			exec_pipe(t_ast *ast_head, t_env *env, t_exec *exec);
void			exec_children(t_ast *ast_node, t_env *env, t_exec *exec);
int				exec_command(char **argv, t_env *env, t_exec *exec);
int				exec_builtin(char **argv, t_env *env, t_exec *exec);
void			exec_finish(char **argv, t_env *env, t_exec *exec);
void			exec_redir_out(t_ast *ast_node, t_exec *exec, t_type type);
void			exec_redir_in(t_ast *ast_node, t_exec *exec, t_type type);
t_exec			*init_fd(void);
void			reset_fd(t_exec *exec);
int				ft_handle_here_doc(char *limiter);

// exec_path
char			**create_pathname(char *command, t_env *env);
char			*find_pathname(char **path);
// exec_utils
char			**tokens_to_char_array(t_token *tokens);
char			**env_to_char_array(t_env *env);
int				envp_size(t_env *env);
// exec_utils2
void			ft_pipe(int *fd);
pid_t			ft_fork(void);

// BUILTIN
int				builtin_cd(char **argv, t_env **env);
int				builtin_echo(char **argv);
bool			builtin_env(t_env *env);
bool			builtin_exit(char **argv);
int				builtin_export(char **argv, t_env **env);
int				builtin_pwd(void);
int				builtin_unset(char **argv, t_env **env);

// builtin_utils
int				builtin_env_update(t_env **env, char *key, char *value);

//signals
void			ctrl_c_handler(int signal);
void			ctrl_backslash_handler(int signal);
void			disable_signal_echo(void);
// UTILS
t_env			*init_env(char **envp);
char			*ft_getenv(char *key, t_env *env);
// free
void			free_token_list(t_token *token_head);
void			free_env_list(t_env *env);
void			free_char_array(char **str);
void			free_token(t_token *token);
// exit
void			ft_exit(char *command);
// debug
void			token_print(t_token *tokens);
void			print_char_array(char **str);
void			check_tokens(t_token *tokens);
void			print_ast(t_ast* node, int level);
char			*token_type_to_string(t_type type);
#endif
