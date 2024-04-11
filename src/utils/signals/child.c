/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:48:44 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/11 23:17:52 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ctrl_c_handler_child(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
}

static void	ctrl_backslash_handler_child(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
}

void	init_child_signals(void)
{
	signal(SIGQUIT, ctrl_backslash_handler_child);
	signal(SIGINT, ctrl_c_handler_child);
}
