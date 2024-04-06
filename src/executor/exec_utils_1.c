/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:53:52 by mott              #+#    #+#             */
/*   Updated: 2024/04/06 15:23:03 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		ft_perror("pipe", strerror(errno));
		return (-1);
	}
	return (EXIT_SUCCESS);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_perror("fork", strerror(errno));
	return (pid);
}

int	set_fd(t_env *env)
{
	env->fd_stdin = dup(STDIN_FILENO);
	if (env->fd_stdin == -1)
	{
		ft_perror("dup", strerror(errno));
		return (-1);
	}
	env->fd_stdout = dup(STDOUT_FILENO);
	if (env->fd_stdout == -1)
	{
		ft_perror("dup", strerror(errno));
		return (-1);
	}
	return (EXIT_SUCCESS);
}

int	reset_fd(t_env *env)
{
	if (dup2(env->fd_stdin, STDIN_FILENO) == -1)
	{
		ft_perror("dup2", strerror(errno));
		return (-1);
	}
	close (env->fd_stdin);
	if (dup2(env->fd_stdout, STDOUT_FILENO) == -1)
	{
		ft_perror("dup2", strerror(errno));
		return (-1);
	}
	close (env->fd_stdout);
	return (EXIT_SUCCESS);
}
