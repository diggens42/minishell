/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:29:05 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/22 13:31:54 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// creates a new dynamically allocated string
// contains same chars as input string
char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*copy;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1) + 1;
	copy = (char *)malloc(len);
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, s1, len);
	return (copy);
}
