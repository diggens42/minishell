/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:40:44 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/04 19:02:34 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//removes single quotes from tokens content
static void process_single_quotes(char **content)
{
	char	*temp;

	temp = *content;
	*content = remove_quotes(*content);
	free(temp);
}

//removes double quotes and expands content inside
static void	process_double_quotes(char **content, t_env *env)
{
	char	*temp;

	temp = *content;
	*content = remove_quotes(*content);
		// fprintf(stderr, "\x1b[33mDQUOTE before: %s\n\x1b[0m", *content);
	free(temp);
	temp = *content;
	*content = expand_double_quote(*content, env);
		// fprintf(stderr, "\x1b[33mDQUOTE after: %s\n\x1b[0m", *content);
	free(temp);
}

//expands a variable within a tokens content
static void	process_dollar_sign(char **content, t_env *env)
{
	char	*temp;

	temp = *content;
	*content = expand_dollar_sign(*content, env);
	free(temp);
}

//expands a variable within a tokens content
static void	process_dqmark_sign(char **content, t_env *env)
{
	char	*temp;

	temp = *content;
	*content = ft_itoa(env->exit_status);
	free(temp);
}

// //expands wildcards within a tokens content and creates a token for each match
// static void process_wildcard(char **content)
// {
// 	char	*expanded_content;
// 	char	*path;

// 	expanded_content = expand_wildcard(token->content);
// 	path = ft_strtok(expanded_content, " ");
// 	if (path != NULL)
// 	{
// 		free(token->content);
// 		token->content = ft_strdup(path);
// 		token->length = ft_strlen(path);
// 		token->type = COMMAND;
// 		path = ft_strtok(NULL, " ");
// 		wildcard_path_to_token(path, &token);
// 	}
// 	free(expanded_content);
// }

//expands a token based on its type
void	expand(t_cmd **cmd, t_env *env)
{
	t_cmd	*temp;
	int		i;

	temp = *cmd;
	i = 0;
	while (temp->argv[i] != NULL)
	{
		// fprintf(stderr, "\x1b[33mExpander before: %s\n\x1b[0m", temp->argv[i]);
		// fprintf(stderr, "\x1b[33mExpander before: %s\n\x1b[0m", token_type_to_string(*temp->type[i]));
		if (*temp->type[i] == COMMAND)
			proccess_commands(&temp->argv[i], env);
		else if (*temp->type[i] == SINGLE_QUOTE)
			process_single_quotes(&temp->argv[i]);
		else if (*temp->type[i] == DOUBLE_QUOTE)
			process_double_quotes(&temp->argv[i], env);
		else if (*temp->type[i] == DOLLAR)
			process_dollar_sign(&temp->argv[i], env);
		else if (*temp->type[i] == DQMARK)
			process_dqmark_sign(&temp->argv[i], env);
		// else if (*temp->type[i] == WILDCARD)
		// 	process_wildcard(&temp->argv[i]);
		// fprintf(stderr, "\x1b[33mExpander after: %s\n\x1b[0m", temp->argv[i]);
		i++;
	}
}
