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

# include "../Libft/libft.h"

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

typedef struct	s_token
{
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// minishell.c
int		main(int argc, char **argv, char **envp);
void	ms_interactive_mode(t_env *env);
void	ms_exit(void);
void	ms_free_token_list(t_token *tokens);

// parser.c
t_token	*ms_parser(t_token *tokens, char *user_input);
int		ms_count_words(char *str);
int		ms_count_characters(char *str);

// exec_builtins.c
void	ms_execute(t_token *tokens, t_env *env);

// exec_commands.c
void	ms_execute_commands(t_token *tokens, t_env *env);
char	**ms_create_pathname(t_token *tokens, t_env *env);
char	*ms_find_pathname(char **path);
char	**ms_tokens_to_char_array(t_token *tokens);

// tokens.c
t_token	*ms_new_token(char *content);
t_token	*ms_last_token(t_token *token);
void	ms_add_back_token(t_token **token, t_token *new_token);
int		ms_tokens_size(t_token *tokens);
void 	ms_print_token(t_token *tokens);

// envp.c
char	**ms_env_to_char_array(t_env *env);
int		ms_envp_size(t_env *env);

//utils
char	*ft_strtok(char	*str, const char *delimiter);
size_t	ft_strspn(const char *str, const char *charset);
size_t	ft_strcspn(const char *str, const char *charset);

// builtin/cd.c
void	ms_cd(t_token *token, t_env *env);

// builtin/echo.c
void	ms_echo(t_token *tokens);

// builtin/env.c
void	ms_env(t_env *env);
void	free_env_node(t_env *node);
t_env	*new_env_node(char *key, char *value);
void	append_env_node(t_env **head, t_env *new_node);
t_env	*init_env(char **envp);
char	*ft_getenv(const char *name, t_env *env);

// builtin/export.c
void	update_env_vars(t_env **env, char *key, char *value);
void	ms_export(t_token *tokens, t_env *env);

// builtin/pwd.c
void	ms_pwd(void);

// builitin/unset.c
void	ms_unset(t_env **env, char *key);
