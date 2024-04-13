/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:01:12 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strndup(const char *str1, size_t n)
{
	char	*str2;
	size_t	len;
	
	len = ft_strlen(str1);
	if (len > n)
		len = n;
	str2 = (char *)ft_calloc(len + 1, sizeof(char));
	if (str2 == NULL)
		return (NULL);
	ft_strlcpy(str2, str1, len + 1);
	return (str2);
}
