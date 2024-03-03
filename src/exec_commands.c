/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:54:02 by mott              #+#    #+#             */
/*   Updated: 2024/03/03 19:29:27 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_execute_commands(t_token *tokens)
{
	pid_t	pid;
	char	*path = "/bin/ls";
	char	*cmd[] = {"ls", "-la", NULL};
	// extern char **environ;
	(void)tokens;

	pid = fork();
	if (pid == 0)
	{
		ft_putchar_fd('X', STDERR_FILENO);
		if (execve(path, cmd, NULL) == -1)
			perror("execve");

		ft_putchar_fd('X', STDERR_FILENO);
	}
	else
		waitpid(pid, NULL, 0);
}
