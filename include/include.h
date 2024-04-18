/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 00:42:34 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/17 18:59:39 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include "../Libft/libft.h"
# include "struct.h"
# include "define.h"

#include <stdio.h> // printf, perror
#include <readline/readline.h> // readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
#include <readline/history.h> // add_history
#include <stdlib.h> // malloc, free, exit, getenv
#include <unistd.h> // write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
#include <fcntl.h> // open
#include <sys/wait.h> // wait, waitpid, wait3, wait4
#include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
#include <sys/stat.h> // stat, lstat, fstat
#include <dirent.h> // opendir, readdir, closedir
#include <string.h> // strerror
#include <sys/ioctl.h> // ioctl
#include <termios.h> // tcsetattr, tcgetattr
#include <curses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <term.h>
#include <stdbool.h>
#include <errno.h>

#endif
