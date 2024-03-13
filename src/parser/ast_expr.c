/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:23 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/13 21:11:33 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_expr(t_token **token, t_ast *last_node)
{
	t_ast	*subtree;

	subtree = NULL;
	if (*token == NULL)
		return (NULL);
	if ((*token)->type == PARENTHESIS_L)
	{
		*token = (*token)->next;
		subtree = ast_expr(token, last_node);
		if ((*token)->type != PARENTHESIS_R)
			return (NULL); //TODO handle unclosed parenthesis
		*token = (*token)->next;
		return (subtree);
	}
	else if ((*token)->type == WORD)
		return (ast_cmd(token));
}
