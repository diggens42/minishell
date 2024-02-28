/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:47:35 by mott              #+#    #+#             */
/*   Updated: 2023/10/27 19:16:30 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str1)
{
	char	*str2;
	size_t	i;

	i = ft_strlen(str1);
	str2 = (char *)malloc(i + 1);
	if (str2 == NULL)
		return (NULL);
	ft_strlcpy(str2, str1, i + 1);
	return (str2);
}
