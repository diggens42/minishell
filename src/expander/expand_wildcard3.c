/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:06:45 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/06 19:30:12 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//checks if a given string matches a wildcard pattern
int	match_wildcard(char *pattern, char *str)
{
	while (*pattern != '\0' && *str != '\0')
	{
		if (*pattern == '*')
			return (match_wildcard(pattern + 1, str) || match_wildcard(pattern, str + 1));
		else if (*pattern == *str)
		{
			pattern++;
			str++;
		}
		else
			return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0' && *str == '\0');
}
