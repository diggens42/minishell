/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/22 19:50:42 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec	*init_fd(void)
{
	t_exec	*exec;

	exec = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (exec == NULL)
		ft_exit("malloc");
	exec->fd_stdin = dup(STDIN_FILENO);
	if (exec->fd_stdin == -1)
		ft_exit("dup");
	exec->fd_stdout = dup(STDOUT_FILENO);
	if (exec->fd_stdout == -1)
		ft_exit("dup");
	exec->exit_status = 0;
	return (exec);
}

void	reset_fd(t_exec *exec)
{
	dup2(exec->fd_stdin, STDIN_FILENO);
	// close (exec->fd_stdin);
	dup2(exec->fd_stdout, STDOUT_FILENO);
	// close (exec->fd_stdout);
	// free(exec);
}

int	exec_main(t_ast *ast_node, t_env *env, t_exec *exec)
{
	if (ast_node->argv != NULL)
		fprintf(stderr, "\x1b[33mEnter exec_main with: %s\n\x1b[0m", ast_node->argv[0]);
	else
		fprintf(stderr, "\x1b[33mEnter exec_main with: %s\n\x1b[0m", token_type_to_string(ast_node->type));
	int	exit_status;

	if (ast_node == NULL)
		return (true);
	if (ast_node->type == AND)
	{
		exit_status = exec_main(ast_node->left, env, exec);
		if (exit_status == true)
			exit_status = exec_main(ast_node->right, env, exec);
	}
	else if (ast_node->type == OR)
	{
		exit_status = exec_main(ast_node->left, env, exec);
		if (exit_status == false)
			exit_status = exec_main(ast_node->right, env, exec);
	}
	else if (ast_node->type == PIPE)
		exit_status = exec_pipe(ast_node, env, exec);
	else if (ast_node->type == REDIR_IN || ast_node->type == REDIR_HEREDOC)
	{
		if (ast_node->left->type == REDIR_HEREDOC)
			exec_main(ast_node->left, env, exec);
		exec_redir_in(ast_node->right, exec, ast_node->type);
		exit_status = exec_main(ast_node->left, env, exec);
	}
	else if (ast_node->type == REDIR_OUT || ast_node->type == REDIR_APPEND)
	{
		exec_redir_out(ast_node->right, exec, ast_node->type);
		exit_status = exec_main(ast_node->left, env, exec);
	}
	else
	{
		exit_status = exec_command(ast_node->argv, env, exec);
	}
	return (exit_status);
}

void	exec_redir_out(t_ast *ast_node, t_exec *exec, t_token_type type)
{
	fprintf(stderr, "\x1b[33mEnter exec_redir_out with %s\n\x1b[0m", ast_node->argv[0]);
	int fd_out;
	struct stat stat_fd_out;
	struct stat stat_fd_stdout;

	if (type == REDIR_OUT)
		fd_out = open(ast_node->argv[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
	{
		ft_putstr_fd("here\n", STDERR_FILENO);
		fd_out = open(ast_node->argv[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (fd_out == -1)
		ft_exit("open");

	fstat(STDOUT_FILENO, &stat_fd_out);
	fstat(exec->fd_stdout, &stat_fd_stdout);

	if (stat_fd_out.st_ino == stat_fd_stdout.st_ino)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			ft_exit("dup2");
	}
	close(fd_out);

}

// reads the input with gnl until LIMITER and sends it to the first pipe
int	ft_handle_here_doc(char *limiter)
{
	fprintf(stderr, "\x1b[33mEnter ft_handle_here_doc with %s\n\x1b[0m", limiter);
	int		fd_pipe[2];
	char	*line;

	ft_pipe(fd_pipe);
	while (42)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			// free(limiter);
			break ;
		}
		ft_putstr_fd(line, fd_pipe[1]);
		free(line);
	}
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}

void	exec_redir_in(t_ast *ast_node, t_exec *exec, t_token_type type)
{
	fprintf(stderr, "\x1b[33mEnter exec_redir_in with %s\n\x1b[0m", ast_node->argv[0]);
	int fd_in;
	struct stat stat_fd_in;
	struct stat stat_fd_stdin;

	if (type == REDIR_IN)
		fd_in = open(ast_node->argv[0], O_RDONLY);
	else
		fd_in = ft_handle_here_doc(ast_node->argv[0]);
	if (fd_in == -1)
		ft_exit("open");

	fstat(STDIN_FILENO, &stat_fd_in);
	fstat(exec->fd_stdin, &stat_fd_stdin);

	if (stat_fd_in.st_ino == stat_fd_stdin.st_ino)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_exit("dup2");
	}
	close(fd_in);
}

bool	exec_pipe(t_ast *ast_node, t_env *env, t_exec *exec)
{
	if (ast_node->argv != NULL)
		fprintf(stderr, "\x1b[33mEnter exec_pipe with: %s\n\x1b[0m", ast_node->argv[0]);
	else
		fprintf(stderr, "\x1b[33mEnter exec_pipe with: %s\n\x1b[0m", token_type_to_string(ast_node->type));
	pid_t	pid;
	int		wstatus;

	pid = ft_fork();
	if (pid == 0)
	{
		exec_children(ast_node, env, exec);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == EXIT_SUCCESS)
		return (true);
	else
		return (false);
}

void	exec_children(t_ast *ast_node, t_env *env, t_exec *exec)
{
	if (ast_node->argv != NULL)
		fprintf(stderr, "\x1b[33mEnter exec_children with: %s\n\x1b[0m", ast_node->argv[0]);
	else
		fprintf(stderr, "\x1b[33mEnter exec_children with: %s\n\x1b[0m", token_type_to_string(ast_node->type));

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
		exec_main(ast_node->left, env, exec);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_exit("dup2");
		close(fd[0]);
		exec_main(ast_node->right, env, exec);
		waitpid(pid, NULL, 0);
	}
}

int	exec_command(char **argv, t_env *env, t_exec *exec)
{
	fprintf(stderr, "\x1b[33mEnter exec_command with %s\n\x1b[0m", argv[0]);
	pid_t	pid;
	int		wstatus;

	if (exec_builtin(argv, env, exec) == true)
		return (true);
	pid = ft_fork(); // TODO
	if (pid == 0)
	{
		exec_finish(argv, env, exec);
	}
	// ft_putstr_fd("here1", STDERR_FILENO);
	waitpid(pid, &wstatus, 0);
	// ft_putstr_fd("here2", STDERR_FILENO);
	// if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == EXIT_SUCCESS)
	// {
	// 	return (true);
	// }
	// else
	// {
	// 	return (false);
	// }
	if (WIFEXITED(wstatus) ==  true)
		return (WEXITSTATUS(wstatus));
	else
		return (EXIT_FAILURE);
}

bool	exec_builtin(char **argv, t_env *env, t_exec *exec)
{
	fprintf(stderr, "\x1b[33mEnter exec_builtin with %s\n\x1b[0m", argv[0]);
	(void)exec;
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

void	exec_finish(char **argv, t_env *env, t_exec *exec)
{
	fprintf(stderr, "\x1b[33mEnter exec_finish with %s\n\x1b[0m", argv[0]);
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
	fprintf(stderr, "\x1b[33mEnter execve with %s\n\x1b[0m", pathname);
	envp = env_to_char_array(env);
	if (execve(pathname, argv, envp) == -1)
	{
		fprintf(stderr, "\x1b[33mexecve error\n\x1b[0m");
		free(pathname);
		free_char_array(argv);
		free_char_array(envp);
		exec->exit_status = 1;
		ft_exit("execve");
	}
	// else
		// exec->exit_status = 0;
}
