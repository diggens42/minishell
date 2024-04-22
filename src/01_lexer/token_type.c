/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:42:19 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/22 20:23:50 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_type	token_type_one_symbol(char *content)
{
	if (*content == '|')
		return (PIPE);
	if (*content == '<')
		return (REDIR_IN);
	if (*content == '>')
		return (REDIR_OUT);
	if (*content == '*')
		return (WILDCARD);
	if (*content == '(')
		return (PARENTHESIS_L);
	if (*content == ')')
		return (PARENTHESIS_R);
	return (COMMAND);
}

static t_type	token_type_two_symbols(char *content)
{
	if (ft_strncmp(content, "&&", 2) == 0)
		return (AND);
	if (ft_strncmp(content, "||", 2) == 0)
		return (OR);
	if (ft_strncmp(content, "<<", 2) == 0)
		return (REDIR_HEREDOC);
	if (ft_strncmp(content, ">>", 2) == 0)
		return (REDIR_APPEND);
	return (COMMAND);
}

t_type	set_type(char *content, int token_length)
{
	t_type	type;

	type = COMMAND;
	if (token_length == 1)
		type = token_type_one_symbol(content);
	else if (token_length == 2)
		type = token_type_two_symbols(content);
	if (token_length > 1)
	{
		if (content[0] == '\'' && content[token_length - 1] == '\'')
			type = SINGLE_QUOTE;
		else if (content[0] == '"' && content[token_length - 1] == '"')
			type = COMMAND;
		else if (ft_strchr(content, '*') != NULL)
			type = WILDCARD;
	}
	return (type);
}
