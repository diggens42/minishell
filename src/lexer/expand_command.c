/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:12:37 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/25 18:13:12 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *expand_quoted(char *start, char *end, t_env *env, t_exec *exec)
{
	char	*quoted_part;
	char	*result;

	quoted_part = ft_substr(start, 1, end - start - 2);
	if (*start == '"')
		result = expand_double_quote(quoted_part, env, exec);
	else
		result = quoted_part;
	if (quoted_part != result)
		free(quoted_part);
	return (result);
}

static char *unquoted_handler(char **new_str, char *current, char *quote_next)
{
	char	*part;
	char	*temp_str;

	part = ft_substr(current, 0, quote_next - current);
	temp_str = ft_strjoin(*new_str, part);
	free(*new_str);
	free(part);
	*new_str = temp_str;
	return (*new_str);
}

static char *quoted_handler(char **new_str, char *quote_next, t_env *env, t_exec *exec)
{
	char	*quote_end;
	char	*part;
	char	*temp_str;
	char	quote_type;

	quote_type = *quote_next;
	quote_end = get_quote_end(quote_next, quote_type);
	if (*quote_end == '\0')
	{
		free(new_str);
		return (NULL); //TODO handle unclosed quotes
	}
	part = expand_quoted(quote_next, quote_end + 1, env, exec);
	temp_str = ft_strjoin(*new_str, part);
	free(part);
	free(*new_str);
	*new_str = temp_str;
	return (*new_str);
}

static char *expand_str_with_quotes(char *str, t_env *env, t_exec *exec)
{
	char	*new_str;
	char	*current;
	char	*quote_next;

	new_str = ft_strdup("");
	current = str;
	while (*current != '\0')
	{
		quote_next = get_quote_start(current);
		if (quote_next > current)
			unquoted_handler(&new_str, current, quote_next);
		if (*quote_next == '\0')
			break ;
		quoted_handler(&new_str, quote_next, env, exec);
		current = get_quote_end(quote_next, *quote_next) + 1;
	}
	return (new_str);
}

static char	*expand_str_with_dqmark(char *content, t_exec *exec)
{
	char	*pos;
	char	*before_dqmark;
	char	*after_dqmark;
	char	*status_str;
	char	*expanded_content;

	pos = ft_strstr(content, "$?");
	if (!pos)
		return (ft_strdup(content));
	before_dqmark = ft_substr(content, 0, pos - content);
	status_str = ft_itoa(exec->exit_status);
	after_dqmark = ft_strjoin(status_str, pos + 2);
	expanded_content = ft_strjoin(before_dqmark, after_dqmark);
	free(before_dqmark);
	free(status_str);
	free(after_dqmark);
	return (expanded_content);
}

void proccess_commands(t_token *token, t_env *env, t_exec *exec)
{
	char	*expanded_content;

	expanded_content = expand_str_with_quotes(token->content, env, exec);
	expanded_content = expand_str_with_dqmark(expanded_content, exec);
	free(token->content);
	token->content = expanded_content;
	token->length = ft_strlen(expanded_content);
}

