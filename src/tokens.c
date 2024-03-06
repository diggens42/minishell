/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:18:10 by mott              #+#    #+#             */
/*   Updated: 2024/03/06 13:21:45 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ms_new_token(char *content)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->content = content;
	new_token->next = NULL;
	return (new_token);
}

t_token	*ms_last_token(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	ms_add_back_token(t_token **token, t_token *new_token)
{
	t_token	*last_token;

	if (*token == NULL)
		*token = new_token;
	else
	{
		last_token = ms_last_token(*token);
		last_token->next = new_token;
	}
}

int	ms_tokens_size(t_token *tokens)
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

void	ms_print_token(t_token *tokens)
{
	while (tokens != NULL)
	{
		ft_printf("%s\n", tokens->content);
		tokens = tokens->next;
	}
}

