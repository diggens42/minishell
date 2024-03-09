/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/09 19:53:47 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute(t_token *token_head, t_env *env)
{
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
		ft_exit();
	else
		execute_commands(token_head, env);
}

void	execute_commands(t_token *token_head, t_env *env)
{
	char	**path;
	char	*pathname;
	char	**argv;
	char	**envp;

	if (ft_strchr(token_head->content, '/') != NULL)
		pathname = token_head->content;
	else
	{
		path = create_pathname(token_head, env);
		pathname = find_pathname(path);
	}
	argv = tokens_to_char_array(token_head);
	envp = env_to_char_array(env);
	if (execve(pathname, argv, envp) == -1)
	{
		perror("execve");
		ft_exit();
	}
}
