/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:44:23 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/13 21:13:32 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_redirect(t_token **token, t_ast *last_node)
{
	t_ast	*redir_node;
	t_ast	*tar_node;
	t_ast	*prev_node;
	
	prev_node = last_node;
	while (*token && ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT
		|| (*token)->type == REDIR_APPEND || (*token)->type == REDIR_HEREDOC))
	{
		redir_node = new_ast_node(*token);
		*token = (*token)->next;
		if (*token == NULL || (*token)->type != WORD)
			return (NULL); //TODO handle missing redirection target
		tar_node = new_ast_node(*token);
		redir_node->left = last_node;
		redir_node->right = tar_node;
		*token = (*token)->next;
		prev_node = redir_node;
	}
	return (prev_node);
}
