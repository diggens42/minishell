/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/08 20:45:51 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_main(t_ast *ast, t_env *env)
{
	// if (ast->cmd != NULL)
	// 	fprintf(stderr, "\x1b[33mexec_main: %s\n\x1b[0m", ast->cmd->argv[0]);
	// else
	// 	fprintf(stderr, "\x1b[33mexec_main: %s\n\x1b[0m", token_type_to_string(ast->type));

	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (ast == NULL)
		return (exit_status);
	else if (ast->subshell == true)
		exit_status = exec_subshell(ast, env);
	else if (ast->type == AND)
	{
		exit_status = exec_main(ast->left, env);
		reset_fd(env);
		if (exit_status == EXIT_SUCCESS)
			exit_status = exec_main(ast->right, env);
	}
	else if (ast->type == OR)
	{
		exit_status = exec_main(ast->left, env);
		reset_fd(env);
		if (exit_status != EXIT_SUCCESS)
			exit_status = exec_main(ast->right, env);
	}
	else if (ast->type == PIPE)
		exit_status = exec_pipe(ast, env, 0);
	else
		exit_status = exec_single_command(ast, env);
	return (exit_status);
}

int	exec_subshell(t_ast *ast, t_env *env)
{
	// if (ast->cmd != NULL)
	// 	fprintf(stderr, "\x1b[33mexec_subshell: %s\n\x1b[0m", ast->cmd->argv[0]);
	// else
	// 	fprintf(stderr, "\x1b[33mexec_subshell: %s\n\x1b[0m", token_type_to_string(ast->type));

	pid_t	pid;
	int		wstatus;
	int		exit_status;

	ast->subshell = false;
	pid = ft_fork();
	if (pid == 0)
	{
		exit_status = exec_main(ast, env);
		exit(exit_status);
	}
	waitpid(pid, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}

int	exec_single_command(t_ast *ast, t_env *env)
{
		// fprintf(stderr, "\x1b[33mexec_single_command: %s\n\x1b[0m", ast->cmd->argv[0]);

	pid_t	pid;
	int		wstatus;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	expand(&ast->cmd, env);
	if (ast->cmd->redir[0] != NULL)
		exit_status = exec_set_redir(ast->cmd->redir, env);
	if (exit_status == EXIT_FAILURE)
		return (exit_status);
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
		// fprintf(stderr, "\x1b[33mexec_builtin: %s\n\x1b[0m", argv[0]);

	char	*temp;
	int		exit_status;

	temp = ft_tolower_str(argv[0]);
	exit_status = -1;
	if (ft_strcmp("echo", temp) == 0)
		exit_status = (builtin_echo(argv));
	else if (ft_strcmp("cd", temp) == 0)
		exit_status = (builtin_cd(argv, &env));
	else if (ft_strcmp("pwd", temp) == 0)
		exit_status = (builtin_pwd());
	else if (ft_strcmp("export", temp) == 0)
		exit_status = (builtin_export(argv, &env));
	else if (ft_strcmp("unset", temp) == 0)
		exit_status = (builtin_unset(argv, &env));
	else if (ft_strcmp("env", temp) == 0)
		exit_status = (builtin_env(env));
	else if (ft_strcmp("exit", temp) == 0)
		exit_status = (builtin_exit(argv));
	free(temp);
	return (exit_status);
}

void	exec_finish(char **argv, t_env *env)
{
		// fprintf(stderr, "\x1b[33mexec_finish: %s\n\x1b[0m", argv[0]);

	char	*pathname;
	char	**envp;

	if (ft_strchr(argv[0], '/') != NULL)
		pathname = create_absolute_path(argv[0]);
	else
		pathname = create_relative_path(argv[0], env);
	envp = env_to_char_array(env);

		// fprintf(stderr, "\x1b[33mexecve: %s\n\x1b[0m", pathname);

	if (execve(pathname, argv, envp) == -1)
	{
		free(pathname);
		free_char_array(argv);
		free_char_array(envp);
		ft_perror(argv[0], strerror(errno));
		exit(EXIT_FAILURE);
	}
}
