/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_chars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:07:24 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/13 15:30:20 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_put_chr_len(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

int	ft_put_str_len(char *str)
{
	int	len;
	int	ret;

	len = 0;
	if (!str)
	{
		ret = ft_put_str_len("(null)");
		if (ret == -1)
			return (-1);
		return (6);
	}
	while (str[len] != '\0')
	{
		ret = write(STDOUT_FILENO, &str[len], 1);
		if (ret == -1)
			return (-1);
		len++;
	}
	return (len);
}
