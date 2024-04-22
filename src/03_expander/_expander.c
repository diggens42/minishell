/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:40:44 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/22 20:24:37 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// removes single quotes from tokens content
static void	process_single_quotes(char **content)
{
	char	*temp;

	temp = *content;
	*content = remove_quotes(*content);
	free(temp);
}

// expands wildcards within a tokens content and creates token for each match
static void	process_wildcard(char **content, t_cmd *cmd, int *index)
{
	char	**expanded_content;
	char	**new_argv;
	t_type	**new_type;

	expanded_content = expand_wildcard(*content);
	new_argv = insert_wildcard(cmd->argv, index, expanded_content);
	cmd->argv = new_argv;
	new_type = set_type_wildcard(cmd->argv, *index);
	free_type_array(cmd->type);
	cmd->type = new_type;
}

// expands a token based on its type
void	expand(t_mini *mini, t_cmd **cmd)
{
	t_cmd	*temp;
	int		i;

	temp = *cmd;
	i = 0;
	while (temp->argv[i] != NULL)
	{
		if (*temp->type[i] == COMMAND)
			proccess_commands(mini, &temp->argv[i]);
		else if (*temp->type[i] == SINGLE_QUOTE)
			process_single_quotes(&temp->argv[i]);
		else if (*temp->type[i] == WILDCARD)
		{
			process_wildcard(&temp->argv[i], *cmd, &i);
			continue ;
		}
		i++;
	}
}
