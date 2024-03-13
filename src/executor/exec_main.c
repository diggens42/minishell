/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/13 15:54:43 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	exec_main(t_ast_node *ast_node, t_env *env)
{
	bool	exit_status;

	if (ast_node == NULL)
		return (true);
	else if (ast_node->type == AND)
	{
		exit_status = exec_main(ast_node->left, env);
		if (exit_status == true)
			exit_status = exec_main(ast_node->right, env);
	}
	else if (ast_node->type == OR)
	{
		exit_status = exec_main(ast_node->left, env);
		if (exit_status == false)
			exit_status = exec_main(ast_node->right, env);
	}
	else if (ast_node->type == PIPE)
		exit_status = exec_pipe(ast_node, env);
	else
		exit_status = exec_command(ast_node->argv, env);
	return (exit_status);
}

bool	exec_pipe(t_ast_node *ast_head, t_env *env)
{
	int		pipe_fd[2];
	pid_t	left_child_pid;
	pid_t	right_child_pid;
	int		left_wstatus;
	int		right_wstatus;

	ft_pipe(pipe_fd);
	left_child_pid = setup_left_child(pipe_fd, ast_head, env);
	close(pipe_fd[1]);
	right_child_pid = setup_right_child(pipe_fd, ast_head, env);
	close(pipe_fd[0]);
	waitpid(left_child_pid, &left_wstatus, 0);
	waitpid(right_child_pid, &right_wstatus, 0);
	if (WIFEXITED(left_wstatus) && WEXITSTATUS(left_wstatus) == EXIT_SUCCESS
		&& WIFEXITED(right_wstatus) && WEXITSTATUS(right_wstatus) == EXIT_SUCCESS)
		return (true);
	else
		return (false);
}

pid_t	setup_left_child(int pipe_fd[2], t_ast_node *ast_head, t_env *env)
{
	pid_t	left_child_pid;

	left_child_pid = fork();
	if (left_child_pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		ft_exit("fork");
	}
	else if (left_child_pid == 0)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			close(pipe_fd[1]);
			ft_exit("dup2");
		}
		close(pipe_fd[1]);
		init_command(ast_head->left->argv, env);
		// execute without pipe()
	}
	return (left_child_pid);
}

pid_t	setup_right_child(int pipe_fd[2], t_ast_node *ast_head, t_env *env)
{
	pid_t	right_child_pid;

	right_child_pid = fork();
	if (right_child_pid == -1)
	{
		close(pipe_fd[0]);
		ft_exit("fork");
	}
	else if (right_child_pid == 0)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			close(pipe_fd[0]);
			ft_exit("dup2");
		}
		close(pipe_fd[0]);
		init_command(ast_head->right->argv, env);
		// execute without pipe()
	}
	return (right_child_pid);
}

bool	exec_command(char **argv, t_env *env)
{
	pid_t	pid;
	int		wstatus;

	// if builtin
	if (ft_strcmp("exit", argv[0]) == 0)
		ft_exit(NULL);
	// else
	pid = fork();
	if (pid == 0)
	{
		init_command(argv, env);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == EXIT_SUCCESS)
		return (true);
	else
		return (false);
}

void	execute(t_token *token_head, t_env *env)
{
	// check argv[0]
	if (ft_strcmp("echo", token_head->content) == 0)
		builtin_echo(token_head);
	else if (ft_strcmp("cd", token_head->content) == 0)
		builtin_cd(token_head->next, &env);
	else if (ft_strcmp("pwd", token_head->content) == 0)
		builtin_pwd();
	else if (ft_strcmp("export", token_head->content) == 0)
		builtin_export(token_head, env);
	else if (ft_strcmp("unset", token_head->content) == 0)
		builtin_unset(&env, token_head->next->content);
	else if (ft_strcmp("env", token_head->content) == 0)
		builtin_env(env);
	else if (ft_strcmp("exit", token_head->content) == 0)
		ft_exit(NULL);
	// else
	// 	init_command(token_head, env);
}

void	init_command(char **argv, t_env *env)
{
	char	**path;
	char	*pathname;
	char	**envp;

	if (ft_strchr(argv[0], '/') != NULL)
		pathname = argv[0];
	else
	{
		path = create_pathname(argv[0], env);
		pathname = find_pathname(path);
		free_char_array(path);
	}
	envp = env_to_char_array(env);
	// print_char_array(argv);
	if (execve(pathname, argv, envp) == -1)
	{
		ft_exit("execve");
		// exit(errno);
	}
	free(pathname);
	free_char_array(argv);
	free_char_array(envp);
}
