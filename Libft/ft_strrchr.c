/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:47:50 by mott              #+#    #+#             */
/*   Updated: 2024/01/26 12:26:56 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	a;
	size_t			i;

	a = (unsigned char)c;
	i = ft_strlen(str);
	while (i > 0 && str[i] != a)
		i--;
	if (str[i] == a)
		return ((char *)&str[i]);
	return (NULL);
}
