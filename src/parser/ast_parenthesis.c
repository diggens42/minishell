/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parenthesis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:23 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/26 20:46:07 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_parenthesis(t_token **token)
{
	t_ast	*subtree;

	subtree = NULL;
	if (*token == NULL || (*token)->type != PARENTHESIS_L)
		return (NULL);
	advance_and_free_token(token);
	subtree = ast_parser(token);
	if (*token == NULL || (*token)->type != PARENTHESIS_R)
		return (NULL); //TODO handle unclosed parenthesis
	advance_and_free_token(token);
	return (subtree);
}
