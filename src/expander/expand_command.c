/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:12:37 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/09 16:38:07 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *expand_quoted(char *start, char *end, t_env *env)
{
	char	*quoted_part;
	char	*result;

	quoted_part = ft_substr(start, 1, end - start - 2);
	if (*start == '"')
		result = expand_double_quote(quoted_part, env);
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

static char *quoted_handler(char **new_str, char *quote_next, t_env *env)
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
	part = expand_quoted(quote_next, quote_end + 1, env);
	temp_str = ft_strjoin(*new_str, part);
	free(part);
	free(*new_str);
	*new_str = temp_str;
	return (*new_str);
}

static char *expand_str_with_quotes(char *str, t_env *env)
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
		quoted_handler(&new_str, quote_next, env);
		current = get_quote_end(quote_next, *quote_next) + 1;
	}
	return (new_str);
}

static char	*expand_str_with_dqmark(char *content, t_env *env)
{
	char	*pos;
	char	*before_dqmark;
	char	*after_dqmark;
	char	*newstr;
	int		quote_state;

	quote_state = 0;
	newstr = ft_strdup(content);
	pos = newstr;
	while (*pos)
	{
		quote_state = set_quote_state(quote_state, *pos);
		if (*pos == '$' && *(pos + 1) == '?' && quote_state == 0)
		{
			before_dqmark = ft_substr(newstr, 0, pos - newstr);
			after_dqmark = ft_strjoin_free(ft_itoa(env->exit_status), pos + 2);
			free(newstr);
			newstr = ft_strjoin(before_dqmark, after_dqmark);
			pos++;
			free(before_dqmark);
			free(after_dqmark);
		}
		pos++;
	}
	return (newstr);
}

void proccess_commands(char **content, t_env *env)
{
	char	*temp;

	temp = *content;
	*content = expand_str_with_dqmark(*content, env);
	free(temp);
	temp = *content;
	*content = expand_str_with_quotes(*content, env);
	free(temp);
}

