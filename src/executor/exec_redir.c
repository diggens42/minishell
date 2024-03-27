/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:31:22 by mott              #+#    #+#             */
/*   Updated: 2024/03/27 15:32:28 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_redir_out(t_ast *ast, t_type type)
{
	// fprintf(stderr, "\x1b[33mEnter exec_redir_out with %s\n\x1b[0m", ast->cmd->argv[0]);
	int fd_out;
	// struct stat stat_fd_out;
	// struct stat stat_fd_stdout;

	if (type == REDIR_OUT)
		fd_out = open(ast->cmd->argv[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(ast->cmd->argv[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
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

int	exec_redir_in(t_ast *ast, t_type type)
{
	// fprintf(stderr, "\x1b[33mEnter exec_redir_in with %s\n\x1b[0m", ast->cmd->argv[0]);
	int fd_in;
	// struct stat stat_fd_in;
	// struct stat stat_fd_stdin;

	if (type == REDIR_IN)
		fd_in = open(ast->cmd->argv[0], O_RDONLY);
	else
		fd_in = exec_here_doc(ast->cmd->argv[0]);
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
