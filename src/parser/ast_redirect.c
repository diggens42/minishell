/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:44:23 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/14 17:21:44 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//OK
t_ast	*ast_redirect(t_token **token, t_ast *cmd_node)
{
	t_ast	*redirect;
	t_ast	*target;
	
	while (*token && is_redirect((*token)->type))
	{
		redirect = new_ast_node(*token);
		*token = (*token)->next;
		if (*token == NULL || (*token)->type != COMMAND)
			return (NULL); //TODO handle missing redirection target
		target = new_ast_node(*token);
		redirect->left = cmd_node;
		redirect->right = target;
		cmd_node = redirect;
		*token = (*token)->next;
	}
	return (cmd_node);
}

bool	is_redirect(t_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == REDIR_HEREDOC)
		return (1);
	return (0);
}