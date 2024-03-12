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
	WORD,
	SINGLE_QUOTE,		// ''
	DOUBLE_QUOTE,		// ""
	REDIRECT_IN,		// <
	REDIRECT_HERE_DOC,	// <<
	REDIRECT_OUT,		// >
	REDIRECT_APPEND,	// >>
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
}	t_token;

typedef struct	s_ast_node
{
	t_token_type		type;
	char				**argv;
	struct s_ast_node	*top;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// minishell.c
int			main(int argc, char **argv, char **envp);
void		read_eval_print_loop(t_env *env);
char		*find_limiter(char *user_input);

// LEXER
t_token		*tokenizer(char *user_input, t_env *env);
int			set_token_length(char *user_input);
t_token_type	set_token_type(char	*content, int token_length);
void		interpret_token_content(t_token **token_head, t_env *env);
char		*expand_token_content(const char *content, t_env *env);
// token_ops
t_token		*token_new(void);
t_token		*token_last(t_token *token);
void		token_add_back(t_token **token, t_token *new_token);
int			tokens_size(t_token *tokens);

// PARSER
t_ast_node	*build_ast_simple(t_token *tokens);
t_ast_node	*create_ast_node(t_token *token);
char		**tokens_to_char_array2(t_token *tokens);
int			count_word_group(t_token *tokens);

// BUILTIN
void		builtin_cd(t_token *token, t_env **env);
void		builtin_echo(t_token *tokens);
void		builtin_env(t_env *env);
void		builtin_export(t_token *tokens, t_env *env);
void		builtin_pwd(void);
void		builtin_unset(t_env **env, char *key);
// builtin_utils
void		update_env(t_env **env, char *key, char *value);

// EXECUTOR
void		init_executor(t_ast_node *ast_head, t_env *env);
void		execute_with_pipe(t_ast_node *ast_head, t_env *env);
pid_t		setup_left_child(int pipe_fd[2], t_ast_node *ast_head, t_env *env);
pid_t		setup_right_child(int pipe_fd[2], t_ast_node *ast_head, t_env *env);
void 		execute_without_pipe(char **argv, t_env *env);
void		init_command(char **argv, t_env *env);
// void		execute(t_token *token_head, t_env *env);
// void		init_command(t_token *token_head, t_env *env);
// void		execute_in_child(char *pathname, char **argv, char **envp);
// exector_utils
char		**create_pathname(char *command, t_env *env);
// char		**create_pathname(t_token *tokens, t_env *env);
char		*find_pathname(char **path);
char		**tokens_to_char_array(t_token *tokens);
char		**env_to_char_array(t_env *env);
int			envp_size(t_env *env);

// UTILS
t_env		*init_env(char **envp);
char		*ft_strtok(char	*str, const char *delimiter);
size_t		ft_strspn(const char *str, const char *charset);
size_t		ft_strcspn(const char *str, const char *charset);
char		*ft_getenv(const char *name, t_env *env);
void		ft_exit(void);
// free
void		free_token_list(t_token *token_head);
void		free_env_list(t_env *env);
void		free_env_node(t_env *node);
void		free_char_array(char **str);
//debug
void		token_print(t_token *tokens);
void		print_char_array(char **str);

//debug
void		check_tokens(t_token *tokens);

#endif
