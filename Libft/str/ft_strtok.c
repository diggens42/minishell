/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:16:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:18:36 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtok(char	*str, const char *delimiter)
{
	static char	*token = NULL;
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
