/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:04:09 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/07 20:39:10 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_echo(char **argv)
{
	bool	new_line;
	int		i;

	new_line = true;
	i = 1;
	while (argv[i] != NULL && ft_strcmp("-n", argv[i]) == 0)
	{
		new_line = false;
		i++;
	}
	while (argv[i] != NULL)
	{
		ft_printf("%s", argv[i]);
		i++;
		if (argv[i] != NULL)
			ft_printf(" ");
	}
	if (new_line == true)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
