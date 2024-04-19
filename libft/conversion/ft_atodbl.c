/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atodbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:27:48 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:29:59 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

double	ft_atodbl(const char *s)
{
	long	int_part;
	double	fract_part;
	double	pow;
	int		sign;

	int_part = 0;
	fract_part = 0;
	sign = 1;
	pow = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32 || *s == '+' || (*s == '-'))
	{
		if (*s == '-')
			sign = -sign;
		++s;
	}
	while (*s != '.' && *s != '\0' && ft_isdigit(*s))
		int_part = (int_part * 10) + (*s++ - '0');
	if (*s == '.')
		++s;
	while (ft_isdigit(*s))
	{
		pow /= 10.0;
		fract_part = fract_part + (*s++ - '0') * pow;
	}
	return (((double)int_part + fract_part) * (double)sign);
}
