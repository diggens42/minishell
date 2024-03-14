/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:42:19 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/14 14:38:54 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//TODO PARENTHESIS
static t_token_type	token_type_one_symbol(char *content)
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

static t_token_type	token_type_two_symbols(char *content)
{
	if (ft_strncmp(content, "&&", 2) == 0)
		return (AND);
	if (ft_strncmp(content, "||", 2) == 0)
		return (OR);
	if (ft_strncmp(content, "<<", 2) == 0)
		return (REDIR_HEREDOC);
	if (ft_strncmp(content, ">>", 2) == 0)
		return (REDIR_APPEND);
	if (ft_strncmp(content, "$?", 2) == 0)
		return (DOLLAR_QMARK);
	if (ft_strncmp(content, "$$", 2) == 0)
		return (DOLLAR_DOLLAR);
	return (COMMAND);
}

t_token_type	set_token_type(char	*content, int token_length)
{
	t_token_type	type;

	type = COMMAND;
	if (token_length == 1)
		type = token_type_one_symbol(content);
	else if (token_length == 2)
		type = token_type_two_symbols(content);
	else if (token_length > 1)
	{
		if (content[0] == '$' && content[1] != '?' && content[1] != '$')
			return (DOLLAR);
		else if (content[0] == '\'' && content[token_length - 1] == '\'')
			type = SINGLE_QUOTE;
		else if (content[0] == '"' && content[token_length - 1] == '"')
			type = DOUBLE_QUOTE;
	}
	return (type);
}
