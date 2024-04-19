/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:19:30 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:19:57 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strcspn(const char *str, const char *charset)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_strchr(charset, str[i]) == NULL)
		i++;
	return (i);
}
