/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:53:52 by mott              #+#    #+#             */
/*   Updated: 2024/04/17 20:09:09 by mott             ###   ########.fr       */
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

int	set_fd(t_mini *mini)
{
	mini->fd_stdin = dup(STDIN_FILENO);
	if (mini->fd_stdin == ERROR)
	{
		ft_perror("dup", strerror(errno));
		return (ERROR);
	}
	mini->fd_stdout = dup(STDOUT_FILENO);
	if (mini->fd_stdout == ERROR)
	{
		ft_perror("dup", strerror(errno));
		return (ERROR);
	}
	return (EXIT_SUCCESS);
}

int	reset_fd(t_mini *mini)
{
	if (dup2(mini->fd_stdin, STDIN_FILENO) == ERROR)
	{
		ft_perror("dup2", strerror(errno));
		return (ERROR);
	}
	if (dup2(mini->fd_stdout, STDOUT_FILENO) == ERROR)
	{
		ft_perror("dup2", strerror(errno));
		return (ERROR);
	}
	return (EXIT_SUCCESS);
}

int	close_fd(t_mini *mini)
{
	if (dup2(mini->fd_stdin, STDIN_FILENO) == ERROR)
	{
		ft_perror("dup2", strerror(errno));
		return (ERROR);
	}
	close (mini->fd_stdin);
	if (dup2(mini->fd_stdout, STDOUT_FILENO) == ERROR)
	{
		ft_perror("dup2", strerror(errno));
		return (ERROR);
	}
	close (mini->fd_stdout);
	return (EXIT_SUCCESS);
}
