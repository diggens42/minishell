/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:14:42 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/13 16:36:44 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_parser(t_token **token)
{
	t_ast	*node;

	if (token == NULL || (*token) == NULL)
		return (NULL);
	node = NULL;
	if ((*token)->type == PIPE)
		node = ast_pipe(token);
	else if ((*token)->type == AND || (*token)->type == OR)
		node = ast_logical(token);
	else
		node = ast_expr(token);
	return (node);
}
