/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:10:15 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/09 23:43:32 by fwahl            ###   ########.fr       */
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
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// exit(130);
}


void	ctrl_backslash_handler(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// Add logic to send SIGQUIT to the currently running command (if any)
}

void	disable_signal_echo(void)
{
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
}

void	init_signals(void)
{
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	disable_signal_echo();
	rl_set_signals();
}
