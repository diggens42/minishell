/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:53:52 by mott              #+#    #+#             */
/*   Updated: 2024/04/03 18:50:56 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
		ft_exit("pipe");
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_exit("fork");
	return (pid);
}

void	init_fd(t_env *env)
{
	env->fd_stdin = dup(STDIN_FILENO);
	if (env->fd_stdin == -1)
		ft_perror("dup", strerror(errno));

	env->fd_stdout = dup(STDOUT_FILENO);
	if (env->fd_stdout == -1)
		ft_perror("dup", strerror(errno));
}

void	reset_fd(t_env *env)
{
	dup2(env->fd_stdin, STDIN_FILENO);
	close (env->fd_stdin);
	dup2(env->fd_stdout, STDOUT_FILENO);
	close (env->fd_stdout);
}
