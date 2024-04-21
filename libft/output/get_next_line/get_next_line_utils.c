/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:47:17 by mott              #+#    #+#             */
/*   Updated: 2024/04/21 18:53:50 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	gn_strlen(char *str)
{
	int	i;

	i = 0;
	while (str != NULL && str[i] != '\0')
		i++;
	return (i);
}

char	*gn_strchr(char *str, char c)
{
	while (str != NULL && *str != '\0')
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

char	*gn_strjoin(char *s1, char *s2)
{
	char	*temp;
	int		i;
	int		j;

	temp = malloc(gn_strlen(s1) + gn_strlen(s2) + 1);
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (s1 != NULL && s1[i] != '\0')
	{
		temp[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 != NULL && s2[j] != '\0')
	{
		temp[i + j] = s2[j];
		j++;
	}
	temp[i + j] = '\0';
	return (temp);
}

char	*gn_substr(char *str, int start, int n)
{
	char	*temp;
	int		i;

	if (str == NULL)
		return (NULL);
	temp = malloc(n + 1);
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		temp[i] = str[start + i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
