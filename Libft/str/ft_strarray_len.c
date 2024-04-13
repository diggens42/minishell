/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:36:41 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/13 15:36:51 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strarray_len(char **array)
{
	int len;

	if (array == NULL)
		return (0);
	len = 0;
	while (array[len] != NULL)
		len++;
	return (len);
}
