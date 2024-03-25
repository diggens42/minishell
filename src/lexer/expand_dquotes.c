/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:15:53 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/25 18:07:37 by fwahl            ###   ########.fr       */
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
	while (content[end] != '\0' && (ft_isalnum(content[end])
		|| content[end] == '_' || content[end] == '/' || content[end] == '.'))
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

//processes a string enclosed in double quotes, expanding variables and concatenating literals
char	*expand_double_quote(const char *content, t_env *env, t_exec *exec)
{
	char	*result;
	char	*var;
	char	*temp;
	char	*exit_status;
	char	c;
	int		i;

	result = NULL;
	i = 0;
	while (content[i])
	{
		if (content[i] == '$' && content [i + 1] == '?')
		{
			i += 2;
			temp = result;
			exit_status = ft_itoa(exec->exit_status);
			result = ft_strjoin(result, exit_status);
			free(temp);
			free(exit_status);
		}
		else if (content[i] == '$')
		{
			i++;
			if ((ft_isalpha(content[i]) || content[i] == '_'))
			{
				var = extract_var(content, &i);
				result = expand_and_concatenate(result, var, env);
				free(var);
			}
			else
				result = ft_strjoin(result, "$");
		}
		else
		{
			c = content[i++];
			temp = ft_calloc(2, sizeof(char));
			temp[0] = c;
			result = ft_strjoin(result, temp);
			free(temp);
		}
	}
	if (!result)
		result = (char *)ft_calloc(1, sizeof(char));
	return (result);
}
