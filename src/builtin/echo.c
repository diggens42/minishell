/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:04:09 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/08 21:28:57 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_echo(t_token *tokens)
{
	bool	new_line;

	new_line = true;
	tokens = tokens->next;
	if (tokens != NULL && !(ft_strcmp("-n", tokens->content)))
	{
		new_line = false;
		tokens = tokens->next;
	}
	while (tokens != NULL)
	{
		printf("%s", tokens->content);
		tokens = tokens->next;
		if (tokens != NULL)
			printf(" ");
	}
	if (new_line == true)
		printf("\n");
}
