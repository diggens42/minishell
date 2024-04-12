/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:53:52 by mott              #+#    #+#             */
/*   Updated: 2024/04/12 00:34:09 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pipe(int *fd)
{
	if (pipe(fd) == ERROR)
	{
		ft_perror("pipe", strerror(errno));
		return (ERROR);
	}
	return (EXIT_SUCCESS);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == ERROR)
		ft_perror("fork", strerror(errno));
	return (pid);
}

int	set_fd(t_env *env)
{
	env->fd_stdin = dup(STDIN_FILENO);
	if (env->fd_stdin == ERROR)
	{
		ft_perror("dup", strerror(errno));
		return (ERROR);
	}
	env->fd_stdout = dup(STDOUT_FILENO);
	if (env->fd_stdout == ERROR)
	{
		ft_perror("dup", strerror(errno));
		return (ERROR);
	}
	return (EXIT_SUCCESS);
}

int	reset_fd(t_env *env)
{
	if (dup2(env->fd_stdin, STDIN_FILENO) == ERROR)
	{
		ft_perror("dup2", strerror(errno));
		return (ERROR);
	}
	if (dup2(env->fd_stdout, STDOUT_FILENO) == ERROR)
	{
		ft_perror("dup2", strerror(errno));
		return (ERROR);
	}
	return (EXIT_SUCCESS);
}

int	close_fd(t_env *env)
{
	if (dup2(env->fd_stdin, STDIN_FILENO) == ERROR)
	{
		ft_perror("dup2", strerror(errno));
		return (ERROR);
	}
	close (env->fd_stdin);
	if (dup2(env->fd_stdout, STDOUT_FILENO) == ERROR)
	{
		ft_perror("dup2", strerror(errno));
		return (ERROR);
	}
	close (env->fd_stdout);
	return (EXIT_SUCCESS);
}
