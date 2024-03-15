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
	SINGLE_QUOTE,		// ''
	DOUBLE_QUOTE,		// ""
	REDIR_IN,		// <
	REDIR_HEREDOC,	// <<
	REDIR_OUT,		// >
	REDIR_APPEND,	// >>
	PIPE,				// |
	DOLLAR,				// $
	DOLLAR_QMARK,		// $?
	DOLLAR_DOLLAR,		// $$
	AND,				// &&
	OR,					// ||
	PARENTHESIS_L,		// (
	PARENTHESIS_R,		// )
	WILDCARD			// *
}	t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	char			*content;
	int				length;
	bool			used;
	struct s_token	*next;
}				t_token;

typedef struct	s_ast
{
	t_token_type	type;
	char			**argv;
	struct s_ast	*top;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

// minishell.c
int			main(int argc, char **argv, char **envp);
void		read_eval_print_loop(t_env *env);
char		*find_limiter(char *user_input);

// LEXER
t_token		*tokenizer(char *user_input, t_env *env);
int			set_token_length(char *user_input);
t_token_type	set_token_type(char	*content, int token_length);
void		expand_token(t_token *token, t_env *env);
char		*expand_dollar_sign(const char *content, t_env *env);
char		*expand_double_quote(const char *content, t_env *env);
char		*expand_wildcard(char *content);
char		*remove_double_quotes(const char *content);
char		*remove_single_quotes(const char *content);
// token_ops
t_token		*token_new(void);
t_token		*token_last(t_token *token);
void		token_add_back(t_token **token, t_token *new_token);
int			tokens_size(t_token *tokens);

// PARSER
t_ast		*ast_parser(t_token **token);
t_ast		*ast_cmd(t_token **token);
t_ast		*ast_redirect(t_token **token, t_ast *cmd_node);
t_ast		*ast_pipe(t_token **token, t_ast *left);
t_ast		*ast_logical(t_token **token, t_ast *left);
t_ast		*ast_parenthesis(t_token **token);
t_ast		*new_ast_node(t_token *token);
char		**token_to_str_array(t_token *tokens);
int			count_command_group(t_token *tokens);
bool		is_redirect(t_token_type type);
bool		is_logical(t_token_type type);
void		print_ast(t_ast* node, int level);

// BUILTIN
// bool		builtin_cd(char **argv, t_env **env);
bool		builtin_echo(char **argv);
bool		builtin_env(t_env *env);
// bool		builtin_export(t_token *tokens, t_env *env);
bool		builtin_pwd(void);
bool		builtin_unset(char *key, t_env **env);
void		builtin_exit(void);
// builtin_utils
void		update_env(t_env **env, char *key, char *value);

// EXECUTOR
// exec_main
bool		exec_main(t_ast *ast_head, t_env *env);
bool		exec_pipe(t_ast *ast_head, t_env *env);
void		exec_children(t_ast *ast_node, t_env *env);
bool 		exec_command(char **argv, t_env *env);
bool		exec_builtin(char **argv, t_env *env);
void		exec_finish(char **argv, t_env *env);
// exec_path
char		**create_pathname(char *command, t_env *env);
char		*find_pathname(char **path);
// exec_utils
char		**tokens_to_char_array(t_token *tokens);
char		**env_to_char_array(t_env *env);
int			envp_size(t_env *env);
// exec_utils2
void		ft_pipe(int *fd);
pid_t		ft_fork(void);

// UTILS
t_env		*init_env(char **envp);
char		*ft_strtok(char	*str, const char *delimiter);
size_t		ft_strspn(const char *str, const char *charset);
size_t		ft_strcspn(const char *str, const char *charset);
char		*ft_getenv(const char *name, t_env *env);
// free
void		free_token_list(t_token *token_head);
void		free_env_list(t_env *env);
void		free_env_node(t_env *node);
void		free_char_array(char **str);
// debug
void		token_print(t_token *tokens);
void		print_char_array(char **str);
// debug
void		check_tokens(t_token *tokens);
// exit
void		ft_exit(char *command);

#endif
