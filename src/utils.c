/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:17:33 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/03 19:04:38 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strtok(char	*str, const char *delimiter)
{
	static char	*token = NULL;
	//TODO static char pointer memory leaks???
	char		*end;
	char		*start;

	if (str != NULL)
		token = str;
	else if (token == NULL)
		return (NULL);
	start = token;
	token += ft_strspn(token, delimiter);
	if (*token == '\0')
	{
		token = NULL;
		return (NULL);
	}
	end = token + ft_strcspn(token, delimiter);
	if (*end != '\0')
	{
		*end = '\0';
		token = end + 1;
	}
	else
		token = NULL;
	return (start);
}

size_t	ft_strspn(const char *str, const char *charset)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_strchr(charset, str[i]) != NULL)
		i++;
	return (i);
}

size_t	ft_strcspn(const char *str, const char *charset)
{
	size_t i;

	i = 0;
	while (str[i] && ft_strchr(charset, str[i]) == NULL)
		i++;
	return (i);
}
