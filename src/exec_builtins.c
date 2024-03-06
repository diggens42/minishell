/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/03 17:48:21 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_execute(t_token *tokens, t_env *env)
{
	if (ft_strcmp("echo", tokens->content) == 0)
		ms_echo(tokens);
	else if (ft_strcmp("cd", tokens->content) == 0)
		ms_cd(tokens);
	else if (ft_strcmp("pwd", tokens->content) == 0)
		ms_pwd();
	else if (ft_strcmp("export", tokens->content) == 0)
		ms_export(tokens, env);
	else if (ft_strcmp("unset", tokens->content) == 0)
		ms_unset(&env, tokens->next->content);
	else if (ft_strcmp("env", tokens->content) == 0)
		ms_env(env);
	else if (ft_strcmp("exit", tokens->content) == 0)
		ms_exit();
	else
		ms_execute_commands(tokens, env);
}
