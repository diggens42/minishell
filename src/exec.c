/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/03 17:09:07 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_execute_builtins(t_token *tokens, char **envp)
{
	(void)envp;
	if (tokens == NULL)
		return;
	if ((ft_strncmp("echo", tokens->content, 4) == 0))
		ms_echo(tokens);
	else if (!(ft_strcmp("cd", tokens->content)))
		ms_cd(tokens);
	else if (!(ft_strcmp("pwd", tokens->content)))
		ms_pwd();
	// else if (!(ft_strcmp("export",tokens->content)))
	// 	ms_export();
	// else if (!(ft_strcmp("unset",tokens->content)))
	// 	ms_unset();
	// else if (!(ft_strcmp("env",tokens->content)))
	// 	ms_env();
	else if (!(ft_strcmp("exit",tokens->content)))
	{
		system("leaks minishell");
		exit(EXIT_SUCCESS);
	}
	// else
	// 	; //TODO execve
}
