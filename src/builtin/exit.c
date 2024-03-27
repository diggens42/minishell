/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:56:05 by mott              #+#    #+#             */
/*   Updated: 2024/03/27 17:12:25 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	valid_num(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str++) == 1)
	{
		if (*str == '\0')
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static char	atoexit(char *str)
{
	char	num;
	int		sign;

	sign = 1;
	num = 0;
	if (*str == '-')
		sign = -sign;
	if (*str == '+' || *str == '-')
		str++;
	while (*str != '\0')
		num = num * 10 + *str++ - '0';
	return (sign * num);
}

int	builtin_exit(char **argv)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (argv[1] == NULL)
		exit(EXIT_SUCCESS);
	else if (argv[2] == NULL)
	{
		if (valid_num(argv[1]) == EXIT_FAILURE)
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(argv[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit (255);
		}
		else
			exit(atoexit(argv[1]));
	}
	else
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
