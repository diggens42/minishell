/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:18:53 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:19:13 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strspn(const char *str, const char *charset)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_strchr(charset, str[i]) != NULL)
		i++;
	return (i);
}
