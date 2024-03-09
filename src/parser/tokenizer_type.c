/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:42:19 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/08 19:00:59 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token_type token_type_one_symbol(char *content)
{
	if (*content == '|')
		return (PIPE);
	if (*content == '<')
		return (REDIRECT_IN);
	if (*content == '>')
		return (REDIRECT_OUT);
	if (*content == '$') //TODO
		return (DOLLAR);
	return (WORD);
}

static t_token_type token_type_two_symbols(char *content)
{
	if (ft_strncmp(content, "&&", 2) == 0)
		return (AND);
	if (ft_strncmp(content, "||", 2) == 0)
		return (OR);
	if (ft_strncmp(content, "<<", 2) == 0)
		return (REDIRECT_HERE_DOC);
	if (ft_strncmp(content, ">>", 2) == 0)
		return (REDIRECT_APPEND);
	if (ft_strncmp(content, "$\"", 2) == 0) //TODO
		return (DOLLAR_QUOTE);
	return (WORD);
}

t_token_type	set_token_type(char	*content, int token_length)
{
	t_token_type type;
	
	type = WORD;
	if (token_length == 1)
		type = token_type_one_symbol(content);
	else if (token_length == 2)
		type = token_type_two_symbols(content);
	else if (token_length > 1)
		{
			if (content[0] == '*' && content[token_length - 1] != '\\')
				type = WILDCARD;
			else if (content[0] == '\'' && content[token_length - 1] == '\'')
				type = SINGLE_QUOTE;
			else if (content[0] == '"' && content[token_length - 1] == '"')
				type = DOUBLE_QUOTE;
		}
	return (type);
}