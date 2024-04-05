/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:54:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/05 17:55:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	quotes_syntax(char *cmd_line)
{
	bool	in_squote;
	bool	in_dquote;
	int		i;

	in_squote = false;
	in_dquote = false;
	i = 0;
	while (cmd_line[i] != '\0')
	{
		if (cmd_line[i] == '\'')
		{
			if (!in_dquote)
				in_squote = !in_squote;
		}
		else if (cmd_line[i] == '"')
		{
			if (!in_squote)
				in_dquote = !in_dquote;
		}
		i++;
	}
	return (in_squote || in_dquote);
}
