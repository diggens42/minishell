/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:40:44 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/10 20:37:43 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//removes single quotes from tokens content
static void	process_single_quotes(char **content)
{
	char	*temp;

	temp = *content;
	*content = remove_quotes(*content);
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

// //expands wildcards within a tokens content and creates token for each match
static void	process_wildcard(char **content, t_cmd *cmd, int i)
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
		if (*temp->type[i] == COMMAND)
			proccess_commands(&temp->argv[i], env);
		else if (*temp->type[i] == SINGLE_QUOTE)
			process_single_quotes(&temp->argv[i]);
		else if (*temp->type[i] == DOLLAR)
			process_dollar_sign(&temp->argv[i], env);
		else if (*temp->type[i] == DQMARK)
			process_dqmark_sign(&temp->argv[i], env);
		else if (*temp->type[i] == WILDCARD)
			process_wildcard(&temp->argv[i], *cmd, i);
		i++;
	}
}
