/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:47:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/01 19:19:10 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_execute_commands(t_token *tokens)
{
	if (!(ft_strcmp("echo",tokens->token)))
		ms_echo(tokens);
	else if (!(ft_strcmp("cd",tokens->token)))
		ms_cd(tokens);
	else if (!(ft_strcmp("pwd",tokens->token)))
		ms_pwd();
	else if (!(ft_strcmp("export",tokens->token)))
		ms_export();
	else if (!(ft_strcmp("unset",tokens->token)))
		ms_unset();
	else if (!(ft_strcmp("env",tokens->token)))
		ms_env();
	else if (!(ft_strcmp("exit",tokens->token)))
		ms_exit();
	else
		; //TODO execve 
}