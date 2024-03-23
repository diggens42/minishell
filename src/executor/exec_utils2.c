/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:53:52 by mott              #+#    #+#             */
/*   Updated: 2024/03/23 11:56:31 by mott             ###   ########.fr       */
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

t_exec	*init_fd(void)
{
	t_exec	*exec;

	exec = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (exec == NULL)
		ft_exit("malloc");
	exec->fd_stdin = dup(STDIN_FILENO);
	if (exec->fd_stdin == -1)
		ft_exit("dup");
	exec->fd_stdout = dup(STDOUT_FILENO);
	if (exec->fd_stdout == -1)
		ft_exit("dup");
	exec->exit_status = 0;
	return (exec);
}

void	reset_fd(t_exec *exec)
{
	dup2(exec->fd_stdin, STDIN_FILENO);
	// close (exec->fd_stdin);
	dup2(exec->fd_stdout, STDOUT_FILENO);
	// close (exec->fd_stdout);
	// free(exec);
}
