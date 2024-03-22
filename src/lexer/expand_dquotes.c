/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:15:53 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/21 19:31:05 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//extracts a variable name or path starting at a specified index
static char	*extract_var(const char *content, int *start)
{
	char	*var_path;
	int		end;
	int		extr;

	extr = *start - 1;
	end = *start;
	if (!(ft_isalpha(content[end]) || content[end] != '_'))
		return (NULL);
	while (content[end] != '\0' && (ft_isalnum(content[end]) || content[end] == '_'
		|| content[end] == '/' || content[end] == '.'))
		end++;
	var_path = ft_substr(content, (unsigned int)extr, (size_t)(end - extr));
	*start = end;
	return (var_path);
}

//expands a variable into its value and concatenates it
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

//appends a single char to the end of the string
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

//processes a string enclosed in double quotes, expanding variables and concatenating literals
char	*expand_double_quote(const char *content, t_env *env)
{
	char	*result;
	char	*var;
	int		i;

	result = NULL;
	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			i++;
			var = extract_var(content, &i);
			result = expand_and_concatenate(result, var, env);
			free(var);
		}
		else
			result = append_char(result, content[i++]);
	}
	if (!result)
		result = (char *)ft_calloc(1, sizeof(char));
	return (result);
}

//removes leading and trailing double quotes from a string
char	*remove_double_quotes(const char *content)
{
	char	*remove_quotes;

	remove_quotes = ft_strdup(content + 1);
	remove_quotes[ft_strlen(remove_quotes) - 1] = '\0';
	return (remove_quotes);
}
