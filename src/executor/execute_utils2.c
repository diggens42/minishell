/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:53:52 by mott              #+#    #+#             */
/*   Updated: 2024/03/12 17:51:32 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		*ft_pipe(void)
{
	int	fd[2];

	if (pipe(fd) == -1);
		ft_exit("pipe");
	return (fd);
}

pid_t	ft_fork(void)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
		ft_exit("fork");
	return (pid);
}

void	ft_exit(char *command)
{
	if (command != NULL)
	{
		perror(command);
		system("leaks minishell");
		exit(EXIT_FAILURE);
	}
	else
	{
		system("leaks minishell");
		exit(EXIT_SUCCESS);
	}
}
