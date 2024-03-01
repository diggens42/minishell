/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:47:43 by mott              #+#    #+#             */
/*   Updated: 2024/03/01 19:34:54 by mott             ###   ########.fr       */
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

# define PROMPT_STD "% "
# define PROMPT_MULTI_LINE "> "
# define PROMPT_HEREDOC "heredoc> "

typedef struct	s_token
{
	char			*content;
	struct s_token	*next;
}	t_token;

// minishell.c
int		main(void);
void	ms_interactive_mode(void);

// parser.c
int	ms_count_words(char *str);
int	ms_count_characters(char *str);
t_token	*ms_parser(char *user_input);
t_token	*ms_new_token(char *content);
t_token	*ms_last_token(t_token *token);
void	ms_token_add_back(t_token **token, t_token *new_token);

// executor.c
void	ms_executor(t_token *tokens);


#include <stdbool.h>


