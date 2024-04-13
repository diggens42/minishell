/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:51:32 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// 1. the dst and src pointers are casted to char pointers
//    to enable byte-by-byte access to memory
// 2. check relative positions of src and dst
//    to decide in which direction to copy
// 3. dest < src (non overlapping or overlaps from start)
//    copy from beginning to end of memory block
// 4. dest > src (overlaps from the end)
//    copy from end to start of memory block
//  --> this way you ensure that 'src' data isn't 
//      overwritten by dst data before copied

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest_ptr;
	const char	*src_ptr;
	size_t		i;

	dest_ptr = dst;
	src_ptr = src;
	i = 0;
	if (dest_ptr < src_ptr)
	{
		while (i < len)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	else if (dest_ptr > src_ptr)
	{
		i = len;
		while (i > 0)
		{
			dest_ptr[i - 1] = src_ptr [i - 1];
			i--;
		}
	}
	return (dst);
}
