/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:40:44 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 15:40:46 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void process_single_quotes(t_token *token)
{
	char	*removed_squotes;
	
	if (token == NULL || token->content == NULL)
		return ;
	removed_squotes = remove_single_quotes(token->content);
	free(token->content);
	token->content = removed_squotes;
	token->length = ft_strlen(removed_squotes);
	token->type = COMMAND;
}

static void	process_double_quotes(t_token *token, t_env *env)
{
	char	*content;
	char	*expanded_content;

	if (token == NULL || token->content == NULL)
		return ;
	content = remove_double_quotes(token->content);
	expanded_content = expand_double_quote(content, env);
	free(token->content);
	token->content = expanded_content;
	token->length = ft_strlen(expanded_content);
	token->type = COMMAND;
}

static void	process_dollar_sign(t_token *token, t_env *env)
{
	char	*expanded_content;

	if (token == NULL)
		return ;
	expanded_content = expand_dollar_sign(token->content, env);
	free(token->content);
	token->content = expanded_content;
	token->length = ft_strlen(expanded_content);
	token->type = COMMAND;
}

void	expand_token(t_token *token, t_env *env)
{
	if (token == NULL)
		return ;
	if (token->type == DOLLAR)
		process_dollar_sign(token, env);
	else if (token->type == DOUBLE_QUOTE)
		process_double_quotes(token, env);
	else if (token->type == SINGLE_QUOTE)
		process_single_quotes(token);
}
