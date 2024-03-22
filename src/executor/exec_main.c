/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/22 15:07:59 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	exec_main(t_ast *ast_node, t_env *env)
{
	// fprintf(stderr, "\x1b[33mEnter exec_main with: %s\n\x1b[0m", ast_node->argv[0]);
	bool				exit_status;
	int					fd_stdout;

	fd_stdout = dup(STDOUT_FILENO); // TODO error
	if (ast_node == NULL)
		return (true);
	if (ast_node->type == AND)
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
	else if (ast_node->type == REDIR_IN || ast_node->type == REDIR_OUT || ast_node->type == REDIR_APPEND)
	{
		exec_redirection(ast_node->right);
		exit_status = exec_main(ast_node->left, env);
		dup2(fd_stdout, STDOUT_FILENO);
		close (fd_stdout);
	}
	else
	{
		exit_status = exec_command(ast_node->argv, env);
	}
	return (exit_status);
}

void	exec_redirection(t_ast *ast_node)
{
	// fprintf(stderr, "\x1b[33mEnter exec_redirection with %s\n\x1b[0m", ast_node->argv[0]);
	int fd;

	fd = open(ast_node->argv[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_exit("open");
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_exit("dup2");
	close(fd);
}

bool	exec_pipe(t_ast *ast_node, t_env *env)
{
	// fprintf(stderr, "\x1b[33mEnter exec_pipe with %s\n\x1b[0m", ast_node->argv[0]);
	pid_t	pid;
	int		wstatus;

	pid = ft_fork();
	if (pid == 0)
	{
		exec_children(ast_node, env);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == EXIT_SUCCESS)
		return (true);
	else
		return (false);
}

void	exec_children(t_ast *ast_node, t_env *env)
{
	// fprintf(stderr, "\x1b[33mEnter exec_children with %s\n\x1b[0m", ast_node->argv[0]);
	int		fd[2];
	pid_t	pid;

	ft_pipe(fd);
	pid = ft_fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_exit("dup2");
		close(fd[1]);
		exec_main(ast_node->left, env);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_exit("dup2");
		close(fd[0]);
		exec_main(ast_node->right, env);
		waitpid(pid, NULL, 0);
	}
}

bool	exec_command(char **argv, t_env *env)
{
	// fprintf(stderr, "\x1b[33mEnter exec_command with %s\n\x1b[0m", argv[0]);
	pid_t	pid;
	int		wstatus;

	if (exec_builtin(argv, env) == true)
		return (true);
	pid = fork();
	if (pid == 0)
	{
		exec_finish(argv, env);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == EXIT_SUCCESS)
		return (true);
	else
		return (false);
}

bool	exec_builtin(char **argv, t_env *env)
{
	// fprintf(stderr, "\x1b[33mEnter exec_builtin with %s\n\x1b[0m", argv[0]);
	if (ft_strcmp("echo", argv[0]) == 0)
		return (builtin_echo(argv));
	if (ft_strcmp("cd", argv[0]) == 0)
		return (builtin_cd(argv, &env));
	if (ft_strcmp("pwd", argv[0]) == 0)
		return (builtin_pwd());
	if (ft_strcmp("export", argv[0]) == 0)
		return (builtin_export(argv, &env));
	if (ft_strcmp("unset", argv[0]) == 0)
		return (builtin_unset(argv, &env));
	if (ft_strcmp("env", argv[0]) == 0)
		return (builtin_env(env));
	if (ft_strcmp("exit", argv[0]) == 0)
		return (builtin_exit(argv));
	return (false);
}

void	exec_finish(char **argv, t_env *env)
{
	// fprintf(stderr, "\x1b[33mEnter exec_finish with %s\n\x1b[0m", argv[0]);
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
	// fprintf(stderr, "\x1b[33mEnter execve with %s\n\x1b[0m", pathname);
	envp = env_to_char_array(env);
	if (execve(pathname, argv, envp) == -1)
	{
		free(pathname);
		free_char_array(argv);
		free_char_array(envp);
		ft_exit("execve");
	}
}
