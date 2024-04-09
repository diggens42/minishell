/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:54:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/09 16:26:06 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	quotes_error(bool in_dquote, bool in_squote)
{
	if (in_squote == true)
		ft_perror_4('\'');
	if (in_dquote == true)
		ft_perror_4('"');
}

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
	quotes_error(in_dquote, in_squote);
	return (in_squote || in_dquote);
}
