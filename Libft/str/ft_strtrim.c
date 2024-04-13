/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 21:51:31 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// checkset: go through "set" and check for match with char 'c'
// ft_strtrim: trims chars present in 'set' from beginning and end of string
// 1st while lop checks and icnrements start if char at s1[start] is in the set
// 2nd while loop decreases len if the char just before len is in the set
// calc len of trim_s (len - start + 1) and allocate memory for trimmed string
// copy the trimmed portion of s1 into new string using strlcpy

int	check_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	trim_len;
	size_t	start;
	char	*trim_s;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len = ft_strlen(s1);
	start = 0;
	while (start < len && check_set(s1[start], set))
		start++;
	while (len > start && check_set(s1[len - 1], set))
		len--;
	trim_len = len - start + 1;
	trim_s = (char *)malloc(trim_len);
	if (trim_s == NULL)
		return (NULL);
	ft_strlcpy(trim_s, &s1[start], trim_len);
	return (trim_s);
}
