/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:15:53 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/12 21:14:18 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//extracts a variable name or path starting at a specified index
static char	*var_extract(const char *content, int *start)
{
	char	*var_path;
	int		end;
	int		extr;

	extr = *start - 1;
	end = *start;
	if (!(ft_isalpha(content[end]) || content[end] == '_'))
		return (NULL);
	while (content[end] != '\0' && (ft_isalnum(content[end])
			|| content[end] == '_' || content[end] == '/'
			|| content[end] == '.'))
		end++;
	var_path = ft_substr(content, (unsigned int)extr, (size_t)(end - extr));
	*start = end;
	return (var_path);
}

static char	*var_expand(t_mini *mini, const char *content, int *i, char *result)
{
	char	*var;
	char	*expanded;
	char	*new_result;

	var = var_extract(content, i);
	expanded = expand_dollar_sign(mini, var);
	new_result = ft_strjoin(result, expanded);
	free(result);
	free(expanded);
	free(var);
	return (new_result);
}

static char	*exit_status_expand(t_mini *mini, char *result)
{
	char	*temp;
	char	*exit_status;

	temp = result;
	exit_status = ft_itoa(mini->exit_status);
	result = ft_strjoin(result, exit_status);
	free(temp);
	free(exit_status);
	return (result);
}

static char	*char_join(char *result, char c)
{
	char	*temp;
	char	*new_result;

	temp = (char *)ft_calloc(2, sizeof(char));
	if (!temp)
		return (result);
	temp[0] = c;
	temp[1] = '\0';
	new_result = ft_strjoin(result, temp);
	free(result);
	free(temp);
	return (new_result);
}

char	*expand_double_quote(t_mini *mini, const char *content)
{
	char	*result;
	int		i;

	result = (char *)ft_calloc(1, sizeof(char));
	i = 0;
	while (content[i])
	{
		if (content[i] == '$' && content [i + 1] == '?')
		{
			i += 2;
			result = exit_status_expand(mini, result);
		}
		else if (content[i] == '$' && content [i + 1] != '?')
		{
			i++;
			if ((ft_isalpha(content[i]) || content[i] == '_'))
				result = var_expand(mini, content, &i, result);
			else
				result = char_join(result, '$');
		}
		else
			result = char_join(result, content[i++]);
	}
	return (result);
}
