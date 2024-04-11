/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_length2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:39:45 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/10 19:34:02 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_single_char_len(char c)
{
	return (ft_strchr("|<>()", c) != NULL);
}

void	handle_command_quotes(bool *quotes, char *quote_type, char current)
{
	if (current == '"' || current == '\'')
	{
		if (!(*quotes))
		{
			*quotes = true;
			*quote_type = current;
		}
		else if (*quote_type == current)
		{
			*quotes = false;
			*quote_type = '\'';
		}
	}
}
