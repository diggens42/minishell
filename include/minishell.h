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

# define PROMPT_STD "% "
# define PROMPT_MULTI_LINE "> "
# define PROMPT_HEREDOC "heredoc> "

typedef enum	e_token_type
{
	WORD,
	SINGLE_QUOTE,		// ''
	DOUBLE_QUOTE,		// ""
	REDIRECT_IN,		// <
	REDIRECT_HERE_DOC,	// <<
	REDIRECT_OUT,		// >
	REDIRECT_APPEND,	// >>
	PIPE,				// |
	DOLLAR,				// $
	DOLLAR_QUOTE,		// $""
	AND,				// &&
	OR,					// ||
	PARENTHESIS,		// ()
	WILDCARD,			// *
	UNKNOWN
}	t_token_type;

typedef struct	s_token
{
	char			*content;
	int				length;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	t_token				*tokens;
	struct s_command	*next;
}	t_command;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// minishell.c
int			main(int argc, char **argv, char **envp);
void		interactive_mode(t_env *env);

// PARSER
t_env		*init_env(char **envp);
t_token		*tokenizer(char *user_input);
t_command	*command_parser(t_token *tokens);
// tokenizer_utils
t_token		*token_new(void);
t_token		*token_last(t_token *token);
void		token_add_back(t_token **token, t_token *new_token);
int			tokens_size(t_token *tokens);
void		token_print(t_token *tokens);
int			is_special_char(char c);
int			is_multi_special_char(char *user_input);
// tokenizer_type
t_token_type	set_token_type(char	*content, int token_length);
// parser_utils
t_command	*command_new(t_token *token);
t_command	*command_last(t_command *command);
void		command_add_back(t_command **command, t_command *new_command);
int			command_size(t_command *command);

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
void		execute(t_command *command, t_env *env);
void		setup_next_command(t_command *command, t_env *env);
void		setup_last_command(t_command *command, t_env *env);
void		execute_builtin(t_command *command, t_env *env);
void		execute_commands(t_command *command, t_env *env);
// exector_utils
char		**create_pathname(t_token *tokens, t_env *env);
char		*find_pathname(char **path);
char		**tokens_to_char_array(t_token *tokens);
char		**env_to_char_array(t_env *env);
int			envp_size(t_env *env);

// UTILS
char		*ft_strtok(char	*str, const char *delimiter);
size_t		ft_strspn(const char *str, const char *charset);
size_t		ft_strcspn(const char *str, const char *charset);
char		*ft_getenv(const char *name, t_env *env);
void		ft_exit(void);
// free
// void	free_token_list(t_token *tokens);
void		free_env_node(t_env *node);

#endif
