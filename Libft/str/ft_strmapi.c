/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:57:54 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// takes a string 's' as first arg
// applies function 'f' to each char of 's' at its index 'i'
// allocate memory for new string f_str
// iterate through each char of 's' and apply 'f' and store it in f_str
// set null terminator

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*f_str;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	f_str = (char *)malloc((len + 1) * sizeof(char));
	if (!f_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		f_str[i] = f(i, s[i]);
		i++;
	}
	f_str[len] = '\0';
	return (f_str);
}
