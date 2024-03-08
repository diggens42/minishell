/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:53:21 by mott              #+#    #+#             */
/*   Updated: 2024/03/08 13:05:47 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command	*command_new(t_token *token)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return (NULL);
	new_command->tokens = token;
	new_command->next = NULL;
	return (new_command);
}

t_command	*command_last(t_command *command)
{
	if (command == NULL)
		return (NULL);
	while (command->next != NULL)
		command = command->next;
	return (command);
}

void	command_add_back(t_command **command, t_command *new_command)
{
	t_command	*last_token;

	if (*command == NULL)
		*command = new_command;
	else
	{
		last_token = command_last(*command);
		last_token->next = new_command;
	}
}

// TODO int->size_t?
int	command_size(t_command *command)
{
	int	i;

	i = 0;
	while (command != NULL)
	{
		command = command->next;
		i++;
	}
	return (i);
}
