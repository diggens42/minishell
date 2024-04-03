/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/27 18:34:27 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_main(t_ast *ast, t_env *env)
{
	// if (ast->cmd->argv != NULL)
	// 	fprintf(stderr, "\x1b[33mEnter exec_main with: %s, \x1b[0m", ast->cmd->argv[0]);
	// else
	// 	fprintf(stderr, "\x1b[33mEnter exec_main with: %s, \x1b[0m", token_type_to_string(ast->type));

	int	exit_status;

	if (ast == NULL)
		return (EXIT_SUCCESS);
	// else if (ast->subshell == true)
	// {
	// 	TODO fork() child process -> exec_main
	// }
	else if (ast->type == AND)
	{
		exit_status = exec_main(ast->left, env);
		if (exit_status == EXIT_SUCCESS)
			exit_status = exec_main(ast->right, env);
	}
	else if (ast->type == OR)
	{
		exit_status = exec_main(ast->left, env);
		if (exit_status != EXIT_SUCCESS)
			exit_status = exec_main(ast->right, env);
	}
	else if (ast->type == PIPE)
	{
		exit_status = exec_pipe(ast, env);
	}
	else
	{
		exit_status = exec_command(ast->cmd->argv, env);
	}
	return (exit_status);
}

// int	exec_pipe(t_ast *ast_node, t_env *env, t_exec *exec)
// {
// 	if (ast_node->argv != NULL)
// 		fprintf(stderr, "\x1b[33mEnter exec_pipe with: %s\n\x1b[0m", ast_node->argv[0]);
// 	else
// 		fprintf(stderr, "\x1b[33mEnter exec_pipe with: %s\n\x1b[0m", token_type_to_string(ast_node->type));
// 	pid_t	pid;
// 	int		wstatus;
// 	// int		exit_status;

// 	exec->in_fork = true;
// 	pid = ft_fork();
// 	if (pid == 0)
// 	{
// 		exec_children(ast_node, env, exec);
// 		// exit(EXIT_SUCCESS);
// 	}
// 	waitpid(pid, &wstatus, 0);
// 	return (WEXITSTATUS(wstatus));
// 	// return (exit_status);
// }

int	exec_pipe(t_ast *ast, t_env *env)
{
	// if (ast->cmd->argv != NULL)
	// 	fprintf(stderr, "\x1b[33mEnter exec_pipe with: %s, \x1b[0m", ast->cmd->argv[0]);
	// else
	// 	fprintf(stderr, "\x1b[33mEnter exec_pipe with: %s, \x1b[0m", token_type_to_string(ast->type));

	int		fd[2];
	int		exit_status;

	ft_pipe(fd);
	exit_status = exec_main(ast->left, env);
	close(fd[1]);
	exit_status = exec_main(ast->right, env);
	close(fd[0]);
	return (exit_status);
}

// int	exec_children(t_ast *ast_node, t_env *env, t_exec *exec)
// {
// 	if (ast_node->argv != NULL)
// 		fprintf(stderr, "\x1b[33mEnter exec_children with: %s\n\x1b[0m", ast_node->argv[0]);
// 	else
// 		fprintf(stderr, "\x1b[33mEnter exec_children with: %s\n\x1b[0m", token_type_to_string(ast_node->type));

// 	int		fd[2];
// 	pid_t	pid;
// 	int		wstatus;
// 	int		exit_status;

// 	ft_pipe(fd);
// 	pid = ft_fork();
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		if (dup2(fd[1], STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2a");
// 			return (EXIT_FAILURE);
// 		}
// 		close(fd[1]);
// 		exit_status = exec_main(ast_node->left, env, exec);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		if (dup2(fd[0], STDIN_FILENO) == -1)
// 		{
// 			perror("dup2b");
// 			return (EXIT_FAILURE);
// 		}
// 		close(fd[0]);
// 		exit_status = exec_main(ast_node->right, env, exec);
// 		waitpid(pid, &wstatus, 0);
// 		return (WEXITSTATUS(wstatus));
// 	}
// 	return (exit_status);
// }

int	exec_command(char **argv, t_env *env)
{
		// fprintf(stderr, "\x1b[33mEnter exec_command with %s, \x1b[0m", argv[0]);

	pid_t	pid;
	int		wstatus;
	int		exit_status;

	exit_status = exec_builtin(argv, env);
	if (exit_status != -1)
		return (exit_status);
	pid = ft_fork();
	if (pid == 0)
	{
		// if (ft_strcmp(child, "left") == 0)
		// {
		// 	close(fd_in);
		// 	if (dup2(fd_out, STDOUT_FILENO) == -1)
		// 	{
		// 		perror("dup2a");
		// 		return (EXIT_FAILURE);
		// }
		// 	close(fd_out);
		// }
		// if (ft_strcmp(child, "right") == 0)
		// {
		// 	close(fd_out);
		// 	if (dup2(fd_in, STDIN_FILENO) == -1)
		// 	{
		// 		perror("dup2b");
		// 		return (EXIT_FAILURE);
		// 	}
		// 	close(fd_in);
		// }
		exec_finish(argv, env);
	}
	waitpid(pid, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}

// int	exec_command(char **argv, t_env *env)
// {
// 	fprintf(stderr, "\x1b[33mEnter exec_command with %s\n\x1b[0m", argv[0]);
// 	int	exit_status;

// 	exit_status = exec_builtin(argv, env);
// 	if (exit_status != -1)
// 		return (exit_status);
// 	exec_finish(argv, env);
// 	return (exit_status);
// }

// int	exec_single_command(char **argv, t_env *env)
// {
// 	// fprintf(stderr, "\x1b[33mEnter exec_single_command with: %s\n\x1b[0m", argv[0]);

// 	pid_t	pid;
// 	int		wstatus;
// 	int		exit_status;

// 	exit_status = exec_builtin(argv, env);
// 	if (exit_status != -1)
// 		return (exit_status);
// 	pid = ft_fork();
// 	if (pid == 0)
// 		exec_finish(argv, env);
// 	waitpid(pid, &wstatus, 0);
// 	return (WEXITSTATUS(wstatus));
// }

int	exec_builtin(char **argv, t_env *env)
{
		// fprintf(stderr, "\x1b[33mEnter exec_builtin with: %s\n\x1b[0m", argv[0]);

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
	return (-1);
}

void	exec_finish(char **argv, t_env *env)
{
		// fprintf(stderr, "\x1b[33mEnter exec_finish with: %s\n\x1b[0m", argv[0]);

	char	*pathname;
	char	**envp;

	if (ft_strchr(argv[0], '/') != NULL)
		pathname = create_absolute_path(argv[0]);
	else
		pathname = create_relative_path(argv[0], env);
	envp = env_to_char_array(env);

 		// fprintf(stderr, "\x1b[33mEnter execve with: %s\n\x1b[0m", pathname);

	if (execve(pathname, argv, envp) == -1)
	{
		free(pathname);
		// free_char_array(argv);
		// free_char_array(envp);
		ft_perror(argv[0], strerror(errno));
		exit(EXIT_FAILURE);
	}
}
