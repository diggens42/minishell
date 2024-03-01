/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:04:09 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/01 17:23:44 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_echo(t_token *tokens)
{
	bool new_line;

	new_line = true;
	tokens = tokens->next;
	if (tokens != NULL && !(ft_strcmp("-n", tokens->token)))
	{
		new_line = false;
		tokens = tokens->next;
	}
	while (tokens != NULL)
	{
		printf("%s", tokens->token);
		tokens = tokens->next;
		if (tokens != NULL)
			printf(" ");
	}
	if (new_line == true)
		printf("\n");
}
