/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:14:42 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/14 18:01:39 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_parser(t_token **token)
{
	t_ast	*node;

	node = NULL;
	if (token == NULL || (*token) == NULL)
		return (NULL);
	while (*token != NULL)
	{
		if ((*token)->type == PARENTHESIS_L)
			node = ast_parenthesis(token);
		else if ((*token)->type == COMMAND)
			node = ast_cmd(token);
		else if (*token != NULL && (*token)->type == PIPE)
			node = ast_pipe(token, node);
		else if (*token != NULL && ((*token)->type == AND || (*token)->type == OR))
			node = ast_logical(token, node);
	}
	return (node);
}
