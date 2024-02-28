/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:47:32 by mott              #+#    #+#             */
/*   Updated: 2023/10/27 19:11:20 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	chr;
	size_t			i;

	chr = (unsigned char)c;
	i = 0;
	while (str[i] != '\0' && str[i] != chr)
		i++;
	if (str[i] == chr)
		return ((char *)&str[i]);
	return (NULL);
}
