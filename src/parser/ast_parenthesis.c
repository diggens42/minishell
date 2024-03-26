/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parenthesis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:23 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/26 18:27:04 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_parenthesis(t_token **token)
{
	t_ast	*subtree;
	t_token	*next_token;

	subtree = NULL;
	if (*token == NULL || (*token)->type != PARENTHESIS_L)
		return (NULL);
	next_token = (*token)->next;
	free_token(*token);
	*token = next_token;
	subtree = ast_parser(token);
	if (*token == NULL || (*token)->type != PARENTHESIS_R)
		return (NULL); //TODO handle unclosed parenthesis
	next_token = (*token)->next;
	free_token(*token);
	*token = next_token;
	return (subtree);
}
