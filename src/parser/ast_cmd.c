/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:58:21 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/18 15:55:13 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_cmd(t_token **token)
{
	t_ast	*cmd_node;
	t_token	*next_token;

	if (token == NULL || *token == NULL || (*token)->type != COMMAND)
		return NULL;
	cmd_node = new_ast_node(*token);
	next_token = (*token)->next;
	free_token(*token);
	*token = next_token;
	while (*token != NULL && (*token)->type == COMMAND)
	{
		next_token = (*token)->next;
		free_token(*token);
		*token = next_token;
	}
	if (*token && is_redirect((*token)->type))
		return (ast_redirect(token, cmd_node));
	return (cmd_node);
}
