/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/07 15:55:33 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//TODO while loop for pipe
void	execute(t_command *command, t_env *env)
{
	if (ft_strcmp("echo", command->tokens->content) == 0)
		builtin_echo(command->tokens);
	else if (ft_strcmp("cd", command->tokens->content) == 0)
		builtin_cd(command->tokens->next, env);
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
	pid_t	child_pid;
	char	**path;
	char	*pathname;
	char	**argv;
	char	**envp;

	child_pid = fork();
	if (child_pid == -1)
		ft_exit();
	if (child_pid == 0)
	{
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
	}
	waitpid(child_pid, NULL, 0);
}
