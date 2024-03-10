/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/10 16:37:32 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_executor(t_ast_node *ast_head, t_env *env)
{
	if (ast_head->type == PIPE)
		execute_with_pipe(ast_head, env);
	else
		execute_without_pipe(ast_head->argv, env);
}

void	execute_with_pipe(t_ast_node *ast_head, t_env *env)
{
	int		pipe_fd[2];
	pid_t	left_child_pid;
	pid_t	right_child_pid;

	if (pipe(pipe_fd) == -1)
 		ft_exit();
	left_child_pid = fork();
	if (left_child_pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		ft_exit();
	}
	else if (left_child_pid == 0)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			close(pipe_fd[1]);
			ft_exit();
		}
		close(pipe_fd[1]);
		init_command(ast_head->left->argv, env);
	}
	close(pipe_fd[1]);
	right_child_pid = fork();
	if (right_child_pid == -1)
	{
		close(pipe_fd[0]);
		ft_exit();
	}
	else if (right_child_pid == 0)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			close(pipe_fd[0]);
			ft_exit();
		}
		close(pipe_fd[0]);
		init_command(ast_head->right->argv, env);
	}
	close(pipe_fd[0]);
	waitpid(left_child_pid, NULL, 0);
	waitpid(right_child_pid, NULL, 0);
}

void execute_without_pipe(char **argv, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		init_command(argv, env);
	}
	waitpid(pid, NULL, 0);
}

// void	execute(t_token *token_head, t_env *env)
// {
// 	if (ft_strcmp("echo", token_head->content) == 0)
// 		builtin_echo(token_head);
// 	else if (ft_strcmp("cd", token_head->content) == 0)
// 		builtin_cd(token_head->next, &env);
// 	else if (ft_strcmp("pwd", token_head->content) == 0)
// 		builtin_pwd();
// 	else if (ft_strcmp("export", token_head->content) == 0)
// 		builtin_export(token_head, env);
// 	else if (ft_strcmp("unset", token_head->content) == 0)
// 		builtin_unset(&env, token_head->next->content);
// 	else if (ft_strcmp("env", token_head->content) == 0)
// 		builtin_env(env);
// 	else if (ft_strcmp("exit", token_head->content) == 0)
// 		ft_exit();
// 	else
// 		init_command(token_head, env);
// }

// void	init_command(t_token *token_head, t_env *env)
// {
// 	char	**path;
// 	char	*pathname;
// 	char	**argv;
// 	char	**envp;

// 	if (ft_strchr(token_head->content, '/') != NULL)
// 		pathname = token_head->content;
// 	else
// 	{
// 		path = create_pathname(token_head, env);
// 		pathname = find_pathname(path);
// 		free_char_array(path);
// 	}
// 	argv = tokens_to_char_array(token_head);
// 	envp = env_to_char_array(env);
// 	execute_in_child(pathname, argv, envp);
// 	free(pathname);
// 	free(argv);
// 	free_char_array(envp);
// }

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
	if (execve(pathname, argv, envp) == -1)
	{
		perror("execve");
		ft_exit();
	}
	free(pathname);
	free_char_array(argv);
	free_char_array(envp);
}

// void execute_in_child(char *pathname, char **argv, char **envp)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (execve(pathname, argv, envp) == -1)
// 		{
// 			perror("execve");
// 			ft_exit();
// 		}
// 	}
// 	waitpid(pid, NULL, 0);
// }
