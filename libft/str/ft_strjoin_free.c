/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:38:11 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/13 15:38:12 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *str1, const char *str2)
{
	char	*newstr;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (str1 != NULL)
		len1 = ft_strlen(str1);
	if (str2 != NULL)
		len2 = ft_strlen(str2);
	newstr = (char *)malloc(len1 + len2 + 1);
	if (newstr == NULL)
		return (NULL);
	if (str1 != NULL)
		ft_strlcpy(newstr, str1, len1 + 1);
	else
		newstr[0] = '\0';
	if (str2 != NULL)
		ft_strlcat(newstr + len1, str2, len2 + 1);
	free(str1);
	return (newstr);
}
