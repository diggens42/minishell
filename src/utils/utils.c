/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:17:33 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/22 20:23:07 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_cmd(t_type type)
{
	if (type == COMMAND)
		return (true);
	if (type == SINGLE_QUOTE)
		return (true);
	if (type == WILDCARD)
		return (true);
	return (false);
}

bool	is_operator(t_type type)
{
	if (type == PIPE)
		return (true);
	if (type == AND)
		return (true);
	if (type == OR)
		return (true);
	return (false);
}

bool	is_redirect(t_type type)
{
	if (type == REDIR_IN)
		return (true);
	if (type == REDIR_OUT)
		return (true);
	if (type == REDIR_APPEND)
		return (true);
	if (type == REDIR_HEREDOC)
		return (true);
	return (false);
}

bool	is_logical(t_type type)
{
	return (type == AND || type == OR);
}

bool	is_parenthesis(t_type type)
{
	return (type == PARENTHESIS_L || type == PARENTHESIS_R);
}
