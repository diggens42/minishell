/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:40:44 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/21 19:17:33 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//expands wildcards within a tokens content and creates a token for each match
static void process_wildcard(t_token *token)
{
	char	*expanded_content;
	char	*path;

	expanded_content = expand_wildcard(token->content);
	path = ft_strtok(expanded_content, " ");
	if (path != NULL)
	{
		free(token->content);
		token->content = ft_strdup(path);
		token->length = ft_strlen(path);
		token->type = COMMAND;
		path = ft_strtok(NULL, " ");
		wildcard_path_to_token(path, &token);
	}
	free(expanded_content);
}

//removes single quotes from tokens content
static void process_single_quotes(t_token *token)
{
	char	*removed_squotes;

	removed_squotes = remove_single_quotes(token->content);
	free(token->content);
	token->content = removed_squotes;
	token->length = ft_strlen(removed_squotes);
	token->type = COMMAND;
}

//removes double quotes and expands content inside
static void	process_double_quotes(t_token *token, t_env *env)
{
	char	*removed_dquotes;
	char	*expanded_content;

	removed_dquotes = remove_double_quotes(token->content);
	expanded_content = expand_double_quote(removed_dquotes, env);
	free(token->content);
	token->content = expanded_content;
	token->length = ft_strlen(expanded_content);
	token->type = COMMAND;
}

//expands a variable within a tokens content
static void	process_dollar_sign(t_token *token, t_env *env)
{
	char	*expanded_content;

	expanded_content = expand_dollar_sign(token->content, env);
	free(token->content);
	token->content = expanded_content;
	token->length = ft_strlen(expanded_content);
	token->type = COMMAND;
}

//expands a token based on its type
void	expand_token(t_token *token, t_env *env)
{
	if (token == NULL || token->content == NULL)
		return ;
	if (token->type == WILDCARD)
		process_wildcard(token);
	else if (token->type == DOLLAR)
		process_dollar_sign(token, env);
	else if (token->type == DOUBLE_QUOTE)
		process_double_quotes(token, env);
	else if (token->type == SINGLE_QUOTE)
		process_single_quotes(token);
}
