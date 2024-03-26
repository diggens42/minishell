/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:58:21 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/26 20:42:46 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_cmd(t_token **token)
{
	t_ast	*cmd_node;

	if (token == NULL || *token == NULL || (*token)->type != COMMAND)
		return NULL;
	cmd_node = new_ast_node(*token);
	advance_and_free_token(token);
	while (*token != NULL && (*token)->type == COMMAND)
		advance_and_free_token(token);
	if (*token && is_redirect((*token)->type))
		return (ast_redirect(token, cmd_node));
	return (cmd_node);
}
