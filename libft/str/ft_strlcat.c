/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:35:42 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// concatenate two strings while avoiding buffer overflows
// calculate dest_len but dont go beyond size given by dest_size
// if dest_len is equal or greater dest_size, the src string cannot be appended
//  --> function then returns total len if there had been enough space
// copy chars from src to dest until dest buffer is almost full
// add null char

size_t	ft_strlcat(char *dest, const char *src, size_t dest_size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dest_len = 0;
	src_len = ft_strlen(src);
	while (dest[dest_len] != '\0' && dest_len < dest_size)
		dest_len++;
	if (dest_len >= dest_size)
		return (dest_size + src_len);
	i = dest_len;
	j = 0;
	while (i < dest_size - 1 && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}
