/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:43:46 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/05 18:49:30 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	parenthesis_syntax(t_token *token)
{
	t_token	*check;
	int		parenthesis;

	check = token;
	parenthesis = 0;
	while (check != NULL)
	{
		if (token->type == PARENTHESIS_L)
			parenthesis++;
		if (token->type == PARENTHESIS_R)
			parenthesis--;
		check = check->next;
	}
	if (parenthesis != 0)
		return (true);
	return (false);
}
