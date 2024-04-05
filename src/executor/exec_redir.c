/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:31:22 by mott              #+#    #+#             */
/*   Updated: 2024/04/05 17:23:17 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_redir_out(char *file)
{
	// fprintf(stderr, "\x1b[33mEnter exec_redir_out with %s\n\x1b[0m", ast->cmd->argv[0]);
	int fd_out;
	// struct stat stat_fd_out;
	// struct stat stat_fd_stdout;

	fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	// fstat(STDOUT_FILENO, &stat_fd_out);
	// fstat(exec->fd_stdout, &stat_fd_stdout);
	// if (stat_fd_out.st_ino == stat_fd_stdout.st_ino)
	// {
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
	// }
	close(fd_out);
	return (EXIT_SUCCESS);
}

int	exec_redir_app(char *file)
{
	// fprintf(stderr, "\x1b[33mEnter exec_redir_out with %s\n\x1b[0m", ast->cmd->argv[0]);
	int fd_out;
	// struct stat stat_fd_out;
	// struct stat stat_fd_stdout;

	fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	// fstat(STDOUT_FILENO, &stat_fd_out);
	// fstat(exec->fd_stdout, &stat_fd_stdout);
	// if (stat_fd_out.st_ino == stat_fd_stdout.st_ino)
	// {
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
	// }
	close(fd_out);
	return (EXIT_SUCCESS);
}

int	exec_redir_in(char *file)
{
	// fprintf(stderr, "\x1b[33mEnter exec_redir_in with %s\n\x1b[0m", ast->cmd->argv[0]);
	int fd_in;
	// struct stat stat_fd_in;
	// struct stat stat_fd_stdin;

	fd_in = open(file, O_RDONLY);
	if (fd_in == -1)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	// fstat(STDIN_FILENO, &stat_fd_in);
	// fstat(exec->fd_stdin, &stat_fd_stdin);
	// if (stat_fd_in.st_ino == stat_fd_stdin.st_ino)
	// {
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
	// }
	close(fd_in);
	return (EXIT_SUCCESS);
}

int	exec_redir_here_doc(char *limiter)
{
	// fprintf(stderr, "\x1b[33mEnter exec_redir_in with %s\n\x1b[0m", ast->cmd->argv[0]);
	int fd_in;
	// struct stat stat_fd_in;
	// struct stat stat_fd_stdin;

	fd_in = exec_here_doc(limiter);
	if (fd_in == -1)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	// fstat(STDIN_FILENO, &stat_fd_in);
	// fstat(exec->fd_stdin, &stat_fd_stdin);
	// if (stat_fd_in.st_ino == stat_fd_stdin.st_ino)
	// {
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
	// }
	close(fd_in);
	return (EXIT_SUCCESS);
}

int	exec_here_doc(char *limiter)
{
	// fprintf(stderr, "\x1b[33mEnter ft_handle_here_doc with %s\n\x1b[0m", limiter);
	int		fd_pipe[2];
	char	*line;

	ft_pipe(fd_pipe);
	while (true)
	{
		ft_putstr_fd(PROMPT_MULTI_LINE, STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd_pipe[1]);
		free(line);
	}
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}
