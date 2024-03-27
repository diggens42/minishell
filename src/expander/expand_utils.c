/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:24:03 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/27 17:00:51 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"

// char *get_quote_start(char *str)
// {
// 	while (*str != '\'' && *str != '"' && *str != '\0')
// 		str++;
// 	return (str);
// }

// char *get_quote_end(char *str, char quote_type)
// {
// 	char	*end;

// 	end = str + 1;
// 	while (*end != quote_type && *end != '\0')
// 		end++;
// 	return (end);
// }

// char	*remove_single_quotes(const char *content)
// {
// 	char	*result;
// 	int		len;

// 	len = ft_strlen(content);
// 	result = (char *)ft_calloc(len - 1, sizeof(char));
// 	if (result == NULL)
// 		return (NULL); //TODO handle malloc error
// 	ft_strlcpy(result, content + 1, len - 1);
// 	return (result);
// }

// //removes leading and trailing double quotes from a string
// char	*remove_double_quotes(const char *content)
// {
// 	char	*remove_quotes;

// 	remove_quotes = ft_strdup(content + 1);
// 	remove_quotes[ft_strlen(remove_quotes) - 1] = '\0';
// 	return (remove_quotes);
// }
