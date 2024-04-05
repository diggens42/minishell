/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/05 17:26:13 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_main(t_ast *ast, t_env *env)
{
	// fprintf(stderr, "\x1b[33mHere!\n\x1b[0m");
	// if (ast->cmd != NULL)
	// 	fprintf(stderr, "\x1b[33mEnter exec_main with: %s\n\x1b[0m", ast->cmd->argv[0]);
	// else
	// 	fprintf(stderr, "\x1b[33mEnter exec_main with: %s\n\x1b[0m", token_type_to_string(ast->type));

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
		exit_status = exec_pipe(ast, env, 0);
	}
	else
	{
		exit_status = exec_single_command(ast, env);
	}
	return (exit_status);
}

// int	exec_pipe(t_ast *ast_node, t_env *env, t_exec *exec)
// {
// 	if (ast->cmd != NULL)
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

int	exec_pipe(t_ast *ast, t_env *env, int lvl)
{
	// if (ast->cmd != NULL)
	// 	fprintf(stderr, "\x1b[33mEnter exec_pipe with: %s\n\x1b[0m", ast->cmd->argv[0]);
	// else
	// 	fprintf(stderr, "\x1b[33mEnter exec_pipe with: %s\n\x1b[0m", token_type_to_string(ast->type));

	int		exit_status;

	if (ast->left->type == PIPE)
		exit_status = exec_pipe(ast->left, env, lvl + 1);
	else
		exit_status = exec_pipe_next(ast->left, env);
	if (lvl != 0)
		exit_status = exec_pipe_next(ast->right, env);
	else
		exit_status = exec_pipe_last(ast->right, env);


	return (exit_status);
}

int	exec_pipe_next(t_ast *ast, t_env *env)
{
	// if (ast->cmd != NULL)
	// 	fprintf(stderr, "\x1b[33mEnter exec_pipe_next with: %s\n\x1b[0m", ast->cmd->argv[0]);
	// else
	// 	fprintf(stderr, "\x1b[33mEnter exec_pipe_next with: %s\n\x1b[0m", token_type_to_string(ast->type));

	int		fd[2];
	pid_t	pid;
	int		exit_status;
	// int		errno;

	exit_status = 0;
	ft_pipe(fd);
	pid = ft_fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_perror("dup2a", strerror(errno)); //TODO right error message?
		close(fd[1]);
		exit_status = exec_pipe_command(ast, env);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_perror("dup2b", strerror(errno)); //TODO right error message?
	close(fd[0]);
	return (exit_status);
}

int	exec_pipe_last(t_ast *ast, t_env *env)
{
	// if (ast->cmd != NULL)
	// 	fprintf(stderr, "\x1b[33mEnter exec_pipe_last with: %s\n\x1b[0m", ast->cmd->argv[0]);
	// else
	// 	fprintf(stderr, "\x1b[33mEnter exec_pipe_last with: %s\n\x1b[0m", token_type_to_string(ast->type));

	pid_t	pid;
	int		wstatus;
	// int		exit_status;

	// exit_status = 0;
	pid = ft_fork();
	if (pid == 0)
	{
		// exit_status = exec_pipe_command(ast->cmd->argv, env);
		exec_pipe_command(ast, env);
	}
	waitpid(pid, &wstatus, 0);
	// return (exit_status);
	return (WEXITSTATUS(wstatus));
}

// int	exec_children(t_ast *ast_node, t_env *env, t_exec *exec)
// {
// 	if (ast->cmd != NULL)
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

// int	exec_command(char **argv, t_env *env)
// {
// 		fprintf(stderr, "\x1b[33mEnter exec_command with %s\n\x1b[0m", argv[0]);

// 	pid_t	pid;
// 	int		wstatus;
// 	int		exit_status;

// 	exit_status = exec_builtin(argv, env);
// 	if (exit_status != -1)
// 		return (exit_status);
// 	pid = ft_fork();
// 	if (pid == 0)
// 	{
// 		// if (ft_strcmp(child, "left") == 0)
// 		// {
// 		// 	close(fd_in);
// 		// 	if (dup2(fd_out, STDOUT_FILENO) == -1)
// 		// 	{
// 		// 		perror("dup2a");
// 		// 		return (EXIT_FAILURE);
// 		// }
// 		// 	close(fd_out);
// 		// }
// 		// if (ft_strcmp(child, "right") == 0)
// 		// {
// 		// 	close(fd_out);
// 		// 	if (dup2(fd_in, STDIN_FILENO) == -1)
// 		// 	{
// 		// 		perror("dup2b");
// 		// 		return (EXIT_FAILURE);
// 		// 	}
// 		// 	close(fd_in);
// 		// }
// 		exec_finish(argv, env);
// 	}
// 	waitpid(pid, &wstatus, 0);
// 	return (WEXITSTATUS(wstatus));
// }

int	exec_pipe_command(t_ast *ast, t_env *env)
{
		// fprintf(stderr, "\x1b[33mEnter exec_pipe_command with %s\n\x1b[0m", argv[0]);

	int	exit_status;

	expand(&ast->cmd, env);
	exit_status = exec_builtin(ast->cmd->argv, env);
	if (exit_status != -1)
		// return (exit_status);
		exit (exit_status);
	exec_finish(ast->cmd->argv, env);
	return (exit_status);
}

int	exec_single_command(t_ast *ast, t_env *env)
{
		// fprintf(stderr, "\x1b[33mEnter exec_single_command with: %s\n\x1b[0m", argv[0]);

	pid_t	pid;
	int		wstatus;
	int		exit_status;
	int		i;

	expand(&ast->cmd, env);
	if (ast->cmd->redir[0] != NULL)
	{
		i = 0;
		// while (ast->cmd->redir[i]->type != 0) //TODO how does redir end? 0, NULL, something else?
		while (ast->cmd->redir[i] != NULL) //TODO how does redir end? 0, NULL, something else?
		{
			if (ast->cmd->redir[i]->type == REDIR_OUT)
				exec_redir_out(ast->cmd->redir[i]->file);

			else if (ast->cmd->redir[i]->type == REDIR_APPEND)
				exec_redir_app(ast->cmd->redir[i]->file);

			else if (ast->cmd->redir[i]->type == REDIR_IN)
				exec_redir_in(ast->cmd->redir[i]->file);

			else if (ast->cmd->redir[i]->type == REDIR_HEREDOC)
				exec_here_doc(ast->cmd->redir[i]->file);
			i++;
		}
	}
	exit_status = exec_builtin(ast->cmd->argv, env);
	if (exit_status != -1)
		return (exit_status);
	pid = ft_fork();
	if (pid == 0)
		exec_finish(ast->cmd->argv, env);
	waitpid(pid, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}

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
