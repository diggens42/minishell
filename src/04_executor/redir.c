/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:31:22 by mott              #+#    #+#             */
/*   Updated: 2024/04/21 13:35:36 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exec_redir_in(t_mini *mini, char *file, int in)
{
	int		fd;
	char	*temp;

	temp = expand_str_with_quotes(mini, file);
	if (in == REDIR_IN)
		fd = open(temp, O_RDONLY);
	else
		fd = exec_here_doc(mini, temp);
	if (fd == ERROR)
	{
		ft_perror(temp, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == ERROR)
	{
		ft_perror("dup2", strerror(errno));
		return (EXIT_FAILURE);
	}
	close(fd);
	free(temp);
	return (EXIT_SUCCESS);
}

static int	exec_redir_out(t_mini *mini, char *file, int out)
{
	int		fd;
	char	*temp;

	temp = expand_str_with_quotes(mini, file);
	fd = open(temp, O_WRONLY | O_CREAT | out, 0644);
	if (fd == ERROR)
	{
		ft_perror(temp, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == ERROR)
	{
		ft_perror("dup2", strerror(errno));
		return (EXIT_FAILURE);
	}
	close(fd);
	free(temp);
	return (EXIT_SUCCESS);
}

int	exec_set_redir(t_mini *mini, t_redir **redir)
{
	int		exit_status;
	int		i;

	i = 0;
	exit_status = EXIT_SUCCESS;
	while (redir[i] != NULL && exit_status == EXIT_SUCCESS)
	{
		if (redir[i]->type == REDIR_OUT)
			exit_status = exec_redir_out(mini, redir[i]->file, O_TRUNC);
		else if (redir[i]->type == REDIR_APPEND)
			exit_status = exec_redir_out(mini, redir[i]->file, O_APPEND);
		else if (redir[i]->type == REDIR_IN)
			exit_status = exec_redir_in(mini, redir[i]->file, REDIR_IN);
		else if (redir[i]->type == REDIR_HEREDOC)
			exit_status = exec_redir_in(mini, redir[i]->file, REDIR_HEREDOC);
		i++;
	}
	return (exit_status);
}
