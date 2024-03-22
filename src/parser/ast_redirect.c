/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:44:23 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/22 18:36:29 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//OK
t_ast	*ast_redirect(t_token **token, t_ast *cmd_node)
{
	t_ast	*redirect;
	t_ast	*target;
	t_token	*next_token;

	while (*token && is_redirect((*token)->type))
	{
		redirect = new_ast_node(*token);
		next_token = (*token)->next;
		free_token(*token);
		*token = next_token;
		if (*token == NULL || (*token)->type != COMMAND)
			return (NULL); //TODO handle missing redirection target
		target = new_ast_node(*token);
		redirect->left = cmd_node;
		redirect->right = target;
		cmd_node = redirect;
		next_token = (*token)->next;
		free_token(*token);
		*token = next_token;
	}
	return (cmd_node);
}

bool	is_redirect(t_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == REDIR_HEREDOC)
		return (1);
	return (0);
}
