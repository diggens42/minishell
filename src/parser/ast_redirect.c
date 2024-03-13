/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:44:23 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/13 16:35:28 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_redirect(t_token **token, t_ast *cmd_node)
{
	t_ast	*redir_node;
	t_ast	*tar_node;

	redir_node = new_ast_node(*token);
	*token = (*token)->next;
	if (*token == NULL || (*token)->type != WORD)
		return (NULL); //TODO handle missing redirection target
	tar_node = new_ast_node(*token);
	redir_node->left = cmd_node;
	redir_node->right = tar_node;
	*token = (*token)->next;
	return (redir_node);
}
