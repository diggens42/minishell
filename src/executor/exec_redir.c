/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:31:22 by mott              #+#    #+#             */
/*   Updated: 2024/04/07 16:20:41 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_set_redir(t_redir **redir, t_env *env)
{
	int		exit_status;
	int		i;

	i = 0;
	exit_status = EXIT_SUCCESS;
	while (redir[i] != NULL && exit_status == EXIT_SUCCESS)
	{
		if (redir[i]->type == REDIR_OUT)
			exit_status = exec_redir_out(redir[i]->file, O_TRUNC);
		else if (redir[i]->type == REDIR_APPEND)
			exit_status = exec_redir_out(redir[i]->file, O_APPEND);
		else if (redir[i]->type == REDIR_IN)
			exit_status = exec_redir_in(redir[i]->file, env, REDIR_IN);
		else if (redir[i]->type == REDIR_HEREDOC)
			exit_status = exec_redir_in(redir[i]->file, env, REDIR_HEREDOC);
		i++;
	}
	return (exit_status);
}

int	exec_redir_out(char *file, int out)
{
	// fprintf(stderr, "\x1b[33mexec_redir_out: %s\n\x1b[0m", file);

	int fd;

	fd = open(file, O_WRONLY | O_CREAT | out, 0644);
	if (fd == -1)
	{
		ft_perror(file, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_perror("dup2", strerror(errno));
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	exec_redir_in(char *file, t_env *env, int in)
{
	// fprintf(stderr, "\x1b[33mexec_redir_in: %s\n\x1b[0m", file);

	int fd;

	if (in == REDIR_IN)
		fd = open(file, O_RDONLY);
	else
		fd = exec_here_doc(file, env);
	if (fd == -1)
	{
		ft_perror(file, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_perror("dup2", strerror(errno));
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	exec_here_doc(char *limiter, t_env *env)
{
	// fprintf(stderr, "\x1b[33mexec_here_doc: %s\n\x1b[0m", limiter);

	int		fd[2];
	char	*line;
	char	*temp;

	temp = limiter;
	limiter = ft_strjoin(limiter, "\n");
	free(temp);
	ft_pipe(fd);
	while (true)
	{
		ft_putstr_fd(PROMPT_MULTI_LINE, env->fd_stdout);
		line = get_next_line(env->fd_stdin);
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}
