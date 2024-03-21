/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_squotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:43:39 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/21 19:12:29 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//removes leading and trailing single quotes from a string
char	*remove_single_quotes(const char *content)
{
	char	*result;
	int		len;

	len = ft_strlen(content);
	result = (char *)ft_calloc(len - 1, sizeof(char));
	if (result == NULL)
		return (NULL); //TODO handle malloc error
	ft_strlcpy(result, content + 1, len - 1);
	return (result);
}
