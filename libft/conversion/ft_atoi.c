/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:28:52 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *s)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*s != '\0' && ((*s == ' ' || (*s >= '\t' && *s <= '\r'))))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
		if (*s == '-' || *s == '+')
			return (0);
	}
	while (ft_isdigit(*s))
	{
		result = result * 10 + *s - '0';
		s++;
	}
	return (sign * result);
}
