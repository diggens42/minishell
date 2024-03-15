/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_squotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:43:39 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 14:50:49 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_single_quotes(char *str)
{
	char	*result;
	int		len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	result = (char *)ft_calloc(len - 1, sizeof(char));
	if (result == NULL)
		return (NULL); //TODO handle malloc error
	ft_strlcpy(result, str + 1, len - 1);
	return (result);
}
