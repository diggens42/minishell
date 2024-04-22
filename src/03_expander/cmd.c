/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:12:37 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/22 13:31:44 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_quoted(t_mini *mini, char *start, char *end)
{
	char	*quoted_part;
	char	*result;

	quoted_part = ft_substr(start, 1, end - start - 2);
	if (*start == '"')
		result = expand_double_quote(mini, quoted_part);
	else
		result = quoted_part;
	if (quoted_part != result)
		free(quoted_part);
	return (result);
}

static char	*unquoted_handler(char **new_str, char *current, char *quote_next)
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

static char	*quoted_handler(t_mini *mini, char **new_str, char *quote_next)
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
		return (NULL);
	}
	part = expand_quoted(mini, quote_next, quote_end + 1);
	temp_str = ft_strjoin(*new_str, part);
	free(part);
	free(*new_str);
	*new_str = temp_str;
	return (*new_str);
}

char	*expand_str_with_quotes(t_mini *mini, char *str)
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
		quoted_handler(mini, &new_str, quote_next);
		current = get_quote_end(quote_next, *quote_next) + 1;
	}
	return (new_str);
}

void	proccess_commands(t_mini *mini, char **content)
{
	char	*temp;

	temp = *content;
	*content = expand_dollar_qmark(mini, *content);
	free(temp);
	temp = *content;
	*content = expand_dollar_skip_quoted(mini, *content);
	free(temp);
	temp = *content;
	*content = expand_str_with_quotes(mini, *content);
	free(temp);
}
