/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:08:58 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/11 19:27:00 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_variable_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '/' || c == '.');
}

int	is_special_char(char c)
{
	return (ft_strchr("|<>*()", c) != NULL);
}

int	is_multi_special_char(char *user_input)
{
	const char	*symbols[] = {"&&", "||", "<<", ">>", NULL};
	int			i;

	i = 0;
	while (symbols[i] != NULL)
	{
		if (ft_strncmp(user_input, symbols[i], ft_strlen(symbols[i])) == 0)
			return (ft_strlen(symbols[i]));
		i++;
	}
	return (0);
}
