/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:54:09 by mott              #+#    #+#             */
/*   Updated: 2024/04/08 20:16:40 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_pipe(t_ast *ast, t_env *env, int lvl)
{
	// if (ast->cmd != NULL)
	// 	fprintf(stderr, "\x1b[33mexec_pipe: %s\n\x1b[0m", ast->cmd->argv[0]);
	// else
	// 	fprintf(stderr, "\x1b[33mexec_pipe: %s\n\x1b[0m", token_type_to_string(ast->type));

	int	exit_status;

	if (ast->left->type == PIPE)
		exit_status = exec_pipe(ast->left, env, lvl + 1);
	else
		exit_status = exec_pipe_next(ast->left, env);
	if (lvl > 0)
		exit_status = exec_pipe_next(ast->right, env);
	else
		exit_status = exec_pipe_last(ast->right, env);
	return (exit_status);
}

int	exec_pipe_next(t_ast *ast, t_env *env)
{
	// if (ast->cmd != NULL)
	// 	fprintf(stderr, "\x1b[33mexec_pipe_next: %s\n\x1b[0m", ast->cmd->argv[0]);
	// else
	// 	fprintf(stderr, "\x1b[33mexec_pipe_next: %s\n\x1b[0m", token_type_to_string(ast->type));

	int		fd[2];
	pid_t	pid;
	int		exit_status;
	// int		wstatus;

	exit_status = EXIT_SUCCESS;
	ft_pipe(fd);
	pid = ft_fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_perror("dup2", strerror(errno));
		close(fd[1]);
		exit_status = exec_pipe_command(ast, env);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_perror("dup2", strerror(errno));
	close(fd[0]);
	// waitpid(pid, &wstatus, 0);
	// return (WEXITSTATUS(wstatus));
	return (exit_status);
}

int	exec_pipe_last(t_ast *ast, t_env *env)
{
	// if (ast->cmd != NULL)
	// 	fprintf(stderr, "\x1b[33mexec_pipe_last: %s\n\x1b[0m", ast->cmd->argv[0]);
	// else
	// 	fprintf(stderr, "\x1b[33mexec_pipe_last: %s\n\x1b[0m", token_type_to_string(ast->type));

	pid_t	pid;
	int		wstatus;

	pid = ft_fork();
	if (pid == 0)
		exec_pipe_command(ast, env);
	waitpid(pid, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}

int	exec_pipe_command(t_ast *ast, t_env *env)
{
		// fprintf(stderr, "\x1b[33mexec_pipe_command: %s\n\x1b[0m", ast->cmd->argv[0]);

	int	exit_status;

	exit_status = EXIT_SUCCESS;
	expand(&ast->cmd, env);
	if (ast->cmd->redir[0] != NULL)
		exit_status = exec_set_redir(ast->cmd->redir, env);
	if (exit_status == EXIT_FAILURE)
		exit (exit_status);
		// return (exit_status);
	exit_status = exec_builtin(ast->cmd->argv, env);
	if (exit_status != -1)
		exit (exit_status);
	exec_finish(ast->cmd->argv, env);
	return (exit_status);
}
