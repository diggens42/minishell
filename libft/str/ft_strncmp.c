/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:55:03 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// compare s1 and s2 up to n chars
// cast to unsignd char to ensure comparison is done based on 
//   ASCII values and negative values dont impact result
// return diff if s1 and s2 at the first non-matchign char

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	uc1;
	unsigned char	uc2;
	size_t			i;

	i = 0;
	while ((*s1 != '\0' || *s2 != '\0') && i < n)
	{
		uc1 = (unsigned char)*s1;
		uc2 = (unsigned char)*s2;
		if (uc1 != uc2)
			return (uc1 - uc2);
		s1++;
		s2++;
		i++;
	}
	return (0);
}
