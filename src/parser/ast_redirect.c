/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:44:23 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/27 15:20:24 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_redirect(t_token **token, t_ast *cmd_node)
{
	t_ast	*redirect;

	while (*token && is_redirect((*token)->type))
	{
		redirect = new_ast_node(*token);
		advance_and_free_token(token);
		if (*token == NULL || (*token)->type != COMMAND)
			return (NULL); //TODO handle missing redirection target
		redirect->left = cmd_node;
		redirect->right = new_ast_node(*token);
		cmd_node = redirect;
		advance_and_free_token(token);
	}
	return (cmd_node);
}

bool	is_redirect(t_type type)
{
	if (type == REDIR_IN)
		return (true);
	if (type == REDIR_OUT)
		return (true);
	if (type == REDIR_APPEND)
		return (true);
	if (type == REDIR_HEREDOC)
		return (true);
	return (false);
}
