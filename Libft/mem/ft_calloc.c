/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:48:07 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// 1. count = num of elements you want to allocate memory for
// 2. size = size in bytes of each element
// 3. needed_size calculates total amount of memory required,
//    which is allocated with malloc
// 4. bzero us used to initialize the entire block of memory to zero
// 5. return pointer to newly allocated block of memory

void	*ft_calloc(size_t count, size_t size)
{
	size_t	needed_size;
	void	*ptr;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	needed_size = count * size;
	ptr = malloc(needed_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, needed_size);
	return (ptr);
}
