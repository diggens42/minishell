/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:24:03 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/23 19:27:22 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *get_quote_start(char *str)
{
	while (*str != '\'' && *str != '"' && *str != '\0')
		str++;
	return (str);
}

char *get_quote_end(char *str, char quote_type)
{
	char	*end;

	end = str + 1;
	while (*end != quote_type && *end != '\0')
		end++;
	return (end);
}

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
