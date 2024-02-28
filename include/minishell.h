/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:47:43 by mott              #+#    #+#             */
/*   Updated: 2024/02/28 13:20:10 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// readline, rl_clear_history, rl_on_new_line, re_replace_line, re_redisplay
#include <readline/readline.h>

// add_history
#include <readline/history.h>

// printf, perror
#include <stdio.h>

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
