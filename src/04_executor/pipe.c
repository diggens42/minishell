/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:54:09 by mott              #+#    #+#             */
/*   Updated: 2024/04/22 14:28:16 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// handle pipe commands (expansion, redirections and builtin functions)
static int	exec_pipe_command(t_mini *mini, t_ast *ast)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	expand(mini, &ast->cmd);
	if (ast->cmd->redir[0] != NULL)
		exit_status = exec_set_redir(mini, ast->cmd->redir);
	if (exit_status == EXIT_FAILURE)
		ft_exit(mini, exit_status);
	ast->cmd->argv = new_argv(ast->cmd->argv);
	exit_status = exec_builtin(mini, ast->cmd->argv);
	if (exit_status != ERROR)
		ft_exit(mini, exit_status);
	exec_finish(mini, ast->cmd->argv);
	return (exit_status);
}

static int	exec_pipe_next(t_mini *mini, t_ast *ast)
{
	int		fd[2];
	pid_t	pid;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	ft_pipe(fd);
	pid = ft_fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_perror("dup2", strerror(errno));
		close(fd[1]);
		exit_status = exec_pipe_command(mini, ast);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_perror("dup2", strerror(errno));
	close(fd[0]);
	return (exit_status);
}

static int	exec_pipe_last(t_mini *mini, t_ast *ast)
{
	pid_t	pid;
	int		wstatus;

	pid = ft_fork();
	if (pid == 0)
		exec_pipe_command(mini, ast);
	reset_fd(mini);
	waitpid(pid, &wstatus, 0);
	while (wait(NULL) > 0)
		continue ;
	return (WEXITSTATUS(wstatus));
}

int	exec_pipe(t_mini *mini, t_ast *ast, int lvl)
{
	int	exit_status;

	if (ast->left->type == PIPE)
		exit_status = exec_pipe(mini, ast->left, lvl + 1);
	else
		exit_status = exec_pipe_next(mini, ast->left);
	if (lvl > 0)
		exit_status = exec_pipe_next(mini, ast->right);
	else
		exit_status = exec_pipe_last(mini, ast->right);
	return (exit_status);
}
