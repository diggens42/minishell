/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:24:03 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/20 16:44:31 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_quote_start(char *str)
{
	while (*str != '\'' && *str != '"' && *str != '\0')
		str++;
	return (str);
}

char	*get_quote_end(char *str, char quote_type)
{
	char	*end;

	end = str + 1;
	while (*end != quote_type && *end != '\0')
		end++;
	return (end);
}

//removes leading and trailing double quotes from a string
char	*remove_quotes(const char *content)
{
	char	*remove_quotes;

	remove_quotes = ft_strdup(content + 1);
	if (remove_quotes == NULL)
		return (NULL);
	remove_quotes[ft_strlen(remove_quotes) - 1] = '\0';
	return (remove_quotes);
}

int	set_quote_state(int quote_state, char c)
{
	if (c == '\'')
	{
		if (quote_state == 1)
			return (0);
		else
			return (1);
	}
	else if (c == '"')
	{
		if (quote_state == 2)
			return (0);
		else
			return (2);
	}
	return (quote_state);
}
