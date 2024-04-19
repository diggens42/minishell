/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:29:48 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_digit_counter(int n)
{
	int	digits;

	digits = 1;
	while (n >= 10)
	{
		digits++;
		n = n / 10;
	}
	return (digits);
}

char	*ft_digit_output(int n, int digits, int sign)
{
	char	*str;
	int		i;

	i = 0;
	if (sign == -1)
		digits++;
	str = (char *)malloc((digits + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (sign == -1)
	{
		str[i] = '-';
		i++;
	}
	str[digits] = '\0';
	while (digits > i)
	{
		digits--;
		str[digits] = '0' + (n % 10);
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		digits;

	sign = 1;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		if (n == -2147483648)
			return (ft_strdup("-2147483648"));
		n = -n;
		sign = -1;
	}
	digits = ft_digit_counter(n);
	str = ft_digit_output(n, digits, sign);
	return (str);
}
