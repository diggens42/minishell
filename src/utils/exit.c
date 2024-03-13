/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:29:20 by mott              #+#    #+#             */
/*   Updated: 2024/03/13 13:30:32 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(char *command)
{
	if (command != NULL)
	{
		perror(command);
		system("leaks minishell");
		exit(EXIT_FAILURE);
	}
	else
	{
		system("leaks minishell");
		exit(EXIT_SUCCESS);
	}
}
