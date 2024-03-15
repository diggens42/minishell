/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:15:53 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 14:57:44 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*extract_var(const char *input, int *start)
{
	char	*var_path;
	int		end;
	int		extr = *start - 1;

	end = *start;
	if (!(ft_isalpha(input[end]) || input[end] != '_'))
		return (NULL);
	while (input[end] != '\0' && (ft_isalnum(input[end]) || input[end] == '_'
		|| input[end] == '/' || input[end] == '.'))
		end++;
	var_path = ft_substr(input, (unsigned int)extr, (size_t)(end - extr));
	*start = end;
	return (var_path);
}

static char	*expand_and_concatenate(char *result, const char *var, t_env *env)
{
	char	*expanded;
	char	*new_result;

	expanded = expand_dollar_sign(var, env);
	new_result = ft_strjoin(result, expanded);
	free(result);
	free(expanded);
	return (new_result);
}

static char	*append_char(char *original, char c)
{
	char	*new_str;
	size_t	original_len;
	size_t	new_len;

	original_len = 0;
	if (original != NULL)
		original_len = ft_strlen(original);
	new_len = original_len + 2;
	new_str = (char *)ft_calloc(new_len, sizeof(char));
	if (new_str == NULL)
		return (original); //TODO handle malloc error
	if (original != NULL)
		ft_strlcpy(new_str, original, original_len + 1);
	new_str[original_len] = c;
	new_str[original_len + 1] = '\0';
	free(original);
	return (new_str);
}

char	*expand_double_quote(const char *input, t_env *env)
{
	char	*result;
	char	*var;
	int		i;

	result = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			var = extract_var(input, &i);
			result = expand_and_concatenate(result, var, env);
			free(var);
		}
		else
			result = append_char(result, input[i++]);
	}
	if (!result)
		result = (char *)ft_calloc(1, sizeof(char));
	return (result);
}

char	*remove_double_quotes(const char *input)
{
	char	*remove_quotes;

	if (input == NULL || ft_strlen(input) < 2)
		return (NULL);
	remove_quotes = ft_strdup(input + 1);
	remove_quotes[ft_strlen(remove_quotes) - 1] = '\0';
	return (remove_quotes);
}
