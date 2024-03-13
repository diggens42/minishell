/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:58:21 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/13 20:44:46 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_cmd(t_token **token)
{
	t_ast	*cmd_node;

	if (token == NULL || *token == NULL || (*token)->type != WORD)
		return NULL;
	cmd_node = new_ast_node(*token);
	while (*token != NULL && (*token)->type == WORD)
		*token = (*token)->next;
	if (*token && ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT
		|| (*token)->type == REDIR_APPEND || (*token)->type == REDIR_HEREDOC))
		return (ast_redirect(token, cmd_node));
	if (*token && (*token)->type == PIPE)
		return (ast_pipe(token, cmd_node));
	if (*token && ((*token)->type == AND || (*token)->type == OR))
		return (ast_logical(token, cmd_node));
	if (*token && (*token)->type == PARENTHESIS_L)
		return (ast_expr, cmd_node);
	return (cmd_node);
}
