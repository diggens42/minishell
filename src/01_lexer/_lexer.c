/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:20:32 by mott              #+#    #+#             */
/*   Updated: 2024/04/20 14:45:59 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*tokenizer(char *cmd_line)
{
	t_token	*token_head;
	t_token	*token;

	token_head = NULL;
	while (*cmd_line != '\0')
	{
		while (ft_isspace(*cmd_line) == true)
			cmd_line++;
		if (*cmd_line == '\0')
			break ;
		token = new_token();
		token->length = set_token_length(cmd_line);
		token->content = ft_substr(cmd_line, 0, token->length);
		token->type = set_type(token->content, token->length);
		token_add_back(&token_head, token);
		cmd_line += token->length;
	}
	return (token_head);
}
