/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_append.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:35:13 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/13 15:35:24 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_strarray_append(char **array, char *str)
{
	int	size;
	char **res;

	size = ft_strarray_len(array);
	res = malloc((size + 2) * sizeof(char *));
	if (res == NULL)
		exit(1);
	ft_memcpy((char *)res, (char *)array, size * sizeof(char *));
	res[size] = ft_strdup(str);
	res[size+1] = NULL;
	free(array);
	return (res);
}
