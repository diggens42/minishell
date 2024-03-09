/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:20:32 by mott              #+#    #+#             */
/*   Updated: 2024/03/08 21:30:00 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*command_parser(t_token *tokens)
{
	t_command	*command;
	t_command	*new_command;
	t_token		*last_token;

	command = NULL;
	new_command = NULL;
	while (tokens != NULL)
	{
		if (command == NULL)
			command = command_new(tokens);
		else if (last_token->type != WORD)
		{
			last_token->next = NULL;
			new_command = command_new(tokens);
			command_add_back(&command, new_command);
		}
		last_token = tokens;
		tokens = tokens->next;
	}
	return (command);
}
