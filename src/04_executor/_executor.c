/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _executor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/22 14:31:59 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// creates a child process for the subshell and calls the main function again
static int	exec_subshell(t_mini *mini, t_ast *ast)
{
	pid_t	pid;
	int		wstatus;
	int		exit_status;

	ast->subshell = false;
	pid = ft_fork();
	if (pid == 0)
	{
		exit_status = exec_main(mini, ast);
		ft_exit(mini, exit_status);
	}
	waitpid(pid, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}

// handle single commands: expands command, sets redirections, checks for
// builtin function and forrks a child process
static int	exec_single_command(t_mini *mini, t_ast *ast)
{
	pid_t	pid;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	expand(mini, &ast->cmd);
	if (ast->cmd->redir[0] != NULL)
		exit_status = exec_set_redir(mini, ast->cmd->redir);
	if (exit_status == EXIT_FAILURE)
		return (exit_status);
	ast->cmd->argv = new_argv(ast->cmd->argv);
	exit_status = exec_builtin(mini, ast->cmd->argv);
	if (exit_status != ERROR)
		return (exit_status);
	init_child_signals();
	pid = ft_fork();
	if (pid == 0)
		exec_finish(mini, ast->cmd->argv);
	else
	{
		exit_status = waitpid_exit_stat(pid);
		init_parent_signals();
	}
	return (exit_status);
}

// starting point of the executor, runs recursively through the AST
int	exec_main(t_mini *mini, t_ast *ast)
{
	if (ast == NULL)
		return (mini->exit_status);
	else if (ast->subshell == true)
		mini->exit_status = exec_subshell(mini, ast);
	else if (ast->type == AND)
	{
		mini->exit_status = exec_main(mini, ast->left);
		reset_fd(mini);
		if (mini->exit_status == EXIT_SUCCESS)
			mini->exit_status = exec_main(mini, ast->right);
	}
	else if (ast->type == OR)
	{
		mini->exit_status = exec_main(mini, ast->left);
		reset_fd(mini);
		if (mini->exit_status != EXIT_SUCCESS)
			mini->exit_status = exec_main(mini, ast->right);
	}
	else if (ast->type == PIPE)
		mini->exit_status = exec_pipe(mini, ast, 0);
	else
		mini->exit_status = exec_single_command(mini, ast);
	return (mini->exit_status);
}

// checks for builtin function and executes it
int	exec_builtin(t_mini *mini, char **argv)
{
	char	*temp;

	if (argv[0] == NULL)
		return (EXIT_SUCCESS);
	temp = ft_tolower_str(argv[0]);
	if (ft_strcmp("echo", temp) == 0)
		return (free(temp), builtin_echo(argv));
	else if (ft_strcmp("cd", temp) == 0)
		return (free(temp), builtin_cd(argv, &mini->env));
	else if (ft_strcmp("pwd", temp) == 0)
		return (free(temp), builtin_pwd());
	else if (ft_strcmp("export", temp) == 0)
		return (free(temp), builtin_export(argv, &mini->env));
	else if (ft_strcmp("unset", temp) == 0)
		return (free(temp), builtin_unset(argv, &mini->env));
	else if (ft_strcmp("env", temp) == 0)
		return (free(temp), builtin_env(mini->env));
	else if (ft_strcmp("exit", temp) == 0)
		return (free(temp), builtin_exit(argv, mini));
	return (free(temp), ERROR);
}

// finally executes the command
void	exec_finish(t_mini *mini, char **argv)
{
	char	*pathname;
	char	**envp;

	if (ft_strchr(argv[0], '/') != NULL)
		pathname = create_absolute_path(mini, argv[0]);
	else
		pathname = create_relative_path(mini, argv[0]);
	envp = env_to_char_array(mini->env);
	if (execve(pathname, argv, envp) == ERROR)
	{
		ft_perror(argv[0], strerror(errno));
		free(pathname);
		ft_free_strarray(envp);
		ft_exit(mini, EXIT_FAILURE);
	}
}
