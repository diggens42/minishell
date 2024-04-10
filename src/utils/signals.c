/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:10:15 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/10 19:17:57 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ctrl_c_handler(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_c_handler_child(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
}
void	ctrl_backslash_handler(int signal)
{
	(void)signal;
}

void	ctrl_backslash_handler_child(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
}

void	init_signals(void)
{
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_backslash_handler);
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	rl_set_signals();
}
