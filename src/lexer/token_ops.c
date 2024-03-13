/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:18:10 by mott              #+#    #+#             */
/*   Updated: 2024/03/13 14:16:19 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*token_new(void)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		ft_exit("malloc");
	new_token->content = NULL;
	new_token->type = UNKNOWN;
	new_token->length = 0;
	new_token->next = NULL;
	return (new_token);
}

t_token	*token_last(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	token_add_back(t_token **token, t_token *new_token)
{
	t_token	*last_token;

	if (*token == NULL)
		*token = new_token;
	else
	{
		last_token = token_last(*token);
		last_token->next = new_token;
	}
}

// TODO int->size_t?
int	tokens_size(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens != NULL)
	{
		tokens = tokens->next;
		i++;
	}
	return (i);
}
