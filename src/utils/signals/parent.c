/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:10:15 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/11 23:17:58 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ctrl_c_handler(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	ctrl_backslash_handler(int signal)
{
	(void)signal;
}

void	init_parent_signals(void)
{
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_backslash_handler);

}

void	init_readline_signal_flags(void)
{
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	rl_set_signals();
}