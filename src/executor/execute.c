/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/09 15:18:00 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute(t_command *command, t_env *env)
{
	int	n_commands;
	int	i;

	n_commands = command_size(command);
	i = 0;
	while (i < n_commands - 1)
	{
		setup_next_command(command, env);
		command = command->next;
	}
	setup_last_command(command, env);
}

void	setup_next_command(t_command *command, t_env *env)
{
	int		fd_pipe[2];
	pid_t	pid;

	if (pipe(fd_pipe) == -1)
		ft_exit();
	pid = fork();
	if (pid == -1)
		ft_exit();
	else if (pid == 0)
	{
		close(fd_pipe[0]);
		if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
			ft_exit();
		close(fd_pipe[1]);
		execute_builtin(command, env);
	}
	close(fd_pipe[1]);
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		ft_exit();
	close(fd_pipe[0]);
}

void	setup_last_command(t_command *command, t_env *env)
{
	// int		fd_file;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_exit();
	else if (pid == 0)
	{
		// fd_file = ft_open_file(argv, i);
		// if (dup2(fd_file, STDOUT_FILENO) == -1)
		// 	ft_exit();
		// close(fd_file);
		execute_builtin(command, env);
	}
	waitpid(pid, NULL, 0);
}

//TODO while loop for pipe
void	execute_builtin(t_command *command, t_env *env)
{
	token_print(command->tokens);

	if (ft_strcmp("echo", command->tokens->content) == 0)
		builtin_echo(command->tokens);
	else if (ft_strcmp("cd", command->tokens->content) == 0)
		builtin_cd(command->tokens->next, &env);
	else if (ft_strcmp("pwd", command->tokens->content) == 0)
		builtin_pwd();
	else if (ft_strcmp("export", command->tokens->content) == 0)
		builtin_export(command->tokens, env);
	else if (ft_strcmp("unset", command->tokens->content) == 0)
		builtin_unset(&env, command->tokens->next->content);
	else if (ft_strcmp("env", command->tokens->content) == 0)
		builtin_env(env);
	else if (ft_strcmp("exit", command->tokens->content) == 0)
		ft_exit();
	else
		execute_commands(command, env);
}

void	execute_commands(t_command *command, t_env *env)
{
	// pid_t	child_pid;
	char	**path;
	char	*pathname;
	char	**argv;
	char	**envp;

	// child_pid = fork();
	// if (child_pid == -1)
	// 	ft_exit();
	// if (child_pid == 0)
	// {
		if (ft_strchr(command->tokens->content, '/') != NULL)
			pathname = command->tokens->content;
		else
		{
			path = create_pathname(command->tokens, env);
			pathname = find_pathname(path);
		}
		argv = tokens_to_char_array(command->tokens);
		envp = env_to_char_array(env);
		if (execve(pathname, argv, envp) == -1)
		{
			perror("execve");
			ft_exit();
		}
	// }
	// waitpid(child_pid, NULL, 0);
}
