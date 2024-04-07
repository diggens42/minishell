/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:40:44 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/07 19:41:43 by fwahl            ###   ########.fr       */
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
static void process_wildcard(char **content, t_cmd *cmd, int i)
{
	char	*expanded_content;
	char	**new_argv;
	t_type	**new_type;

	expanded_content = expand_wildcard(*content);
	new_argv = insert_expanded_wc(cmd->argv, i, expanded_content);
	free(expanded_content);
	free_char_array(cmd->argv);
	cmd->argv = new_argv;
	new_type = wc_set_type(cmd->argv);
	free_type_array(cmd->type);
	cmd->type = new_type;
}

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
		else if (*temp->type[i] == WILDCARD)
			process_wildcard(&temp->argv[i], *cmd, i);
		// fprintf(stderr, "\x1b[33mExpander after: %s\n\x1b[0m", temp->argv[i]);
		i++;
	}
}
