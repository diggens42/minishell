/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_unclosed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:54:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/12 00:21:21 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	quotes_error(bool in_dquote, bool in_squote)
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

int	parenthesis_syntax(t_token *token)
{
	t_token	*check;
	int		parenthesis;

	check = token;
	parenthesis = 0;
	while (check != NULL)
	{
		if (check->type == PARENTHESIS_L)
			parenthesis++;
		if (check->type == PARENTHESIS_R)
			parenthesis--;
		if (parenthesis < 0)
		{
			ft_perror_3(check->content);
			return (SYNTAX_ERROR);
		}
		check = check->next;
	}
	if (parenthesis > 0)
	{
		ft_putstr_fd("minishell: unclosed parenthesis\n", STDERR_FILENO);
		return (SYNTAX_ERROR);
	}
	return (EXIT_SUCCESS);
}
