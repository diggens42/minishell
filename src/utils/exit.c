/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:29:20 by mott              #+#    #+#             */
/*   Updated: 2024/03/21 14:36:51 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(char *command)
{
	if (command != NULL)
	{
		perror(command);
		// system("leaks minishell");
		exit(EXIT_FAILURE);
	}
	else
	{
		// system("leaks minishell");
		exit(EXIT_SUCCESS);
	}
}
