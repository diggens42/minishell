/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:00:25 by mott              #+#    #+#             */
/*   Updated: 2023/10/27 19:23:06 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *str, char (*f)(unsigned int, char))
{
	char	*newstr;
	size_t	i;

	newstr = (char *)malloc(ft_strlen(str) + 1);
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		newstr[i] = f(i, str[i]);
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
