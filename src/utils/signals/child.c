/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:48:44 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/22 18:38:25 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ctrl_c_handler_child(int signal)
{
	(void)signal;
	ft_putstr_fd("^C\n", STDERR_FILENO);
}

static void	ctrl_backslash_handler_child(int signal)
{
	(void)signal;
	ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
}

void	init_child_signals(void)
{
	signal(SIGQUIT, ctrl_backslash_handler_child);
	signal(SIGINT, ctrl_c_handler_child);
}
