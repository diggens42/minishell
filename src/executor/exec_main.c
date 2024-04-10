/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/10 19:22:46 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exec_subshell(t_ast *ast, t_env *env)
{
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
	else
	{
		waitpid(pid, &wstatus, 0);
	}
	return (WEXITSTATUS(wstatus));
}

static int	exec_single_command(t_ast *ast, t_env *env)
{
	pid_t	pid;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	expand(&ast->cmd, env);
	if (ast->cmd->redir[0] != NULL)
		exit_status = exec_set_redir(ast->cmd->redir, env);
	if (exit_status == EXIT_FAILURE)
		return (exit_status);
	ast->cmd->argv = new_argv(ast->cmd->argv);
	exit_status = exec_builtin(ast->cmd->argv, env);
	if (exit_status != -1)
		return (exit_status);
	signal(SIGQUIT, ctrl_backslash_handler_child);
	signal(SIGINT, ctrl_c_handler_child);
	pid = ft_fork();
	if (pid == 0)
		exec_finish(ast->cmd->argv, env);
	else
	{
		exit_status = waitpid_exit_stat(pid);
		signal(SIGINT, ctrl_c_handler);
		signal(SIGQUIT, ctrl_backslash_handler);
	}
	return (exit_status);
}

int	exec_main(t_ast *ast, t_env *env)
{
	// if (ast->cmd != NULL)
	// 	fprintf(stderr, "\x1b[33mexec_main: %s\n\x1b[0m", ast->cmd->argv[0]);
	// else
	// 	fprintf(stderr, "\x1b[33mexec_main: %s\n\x1b[0m", token_type_to_string(ast->type));

	if (ast == NULL)
		return (env->exit_status);
	else if (ast->subshell == true)
		env->exit_status = exec_subshell(ast, env);
	else if (ast->type == AND)
	{
		env->exit_status = exec_main(ast->left, env);
		reset_fd(env);
		if (env->exit_status == EXIT_SUCCESS)
			env->exit_status = exec_main(ast->right, env);
	}
	else if (ast->type == OR)
	{
		env->exit_status = exec_main(ast->left, env);
		reset_fd(env);
		if (env->exit_status != EXIT_SUCCESS)
			env->exit_status = exec_main(ast->right, env);
	}
	else if (ast->type == PIPE)
			env->exit_status = exec_pipe(ast, env, 0);
	else
		env->exit_status = exec_single_command(ast, env);
	return (env->exit_status);
}

int	exec_builtin(char **argv, t_env *env)
{
		// fprintf(stderr, "\x1b[33mexec_builtin: %s\n\x1b[0m", argv[0]);

	char	*temp;
	int		exit_status;

	exit_status = -1;
	if (argv[0] == NULL)
		return (exit_status);
	temp = ft_tolower_str(argv[0]);
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
