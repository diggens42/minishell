/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:16:51 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/13 22:05:52 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// 1. void *ptr: pointer to memory area that needs to be set to zero
// 2. n: number of bytes to set to zero

void	ft_bzero(void *ptr, size_t n)
{
	ft_memset(ptr, 0, n);
}
