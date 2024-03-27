/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:15:53 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/27 17:00:39 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"

// //extracts a variable name or path starting at a specified index
// static char	*var_extract(const char *content, int *start)
// {
// 	char	*var_path;
// 	int		end;
// 	int		extr;

// 	extr = *start - 1;
// 	end = *start;
// 	if (!(ft_isalpha(content[end]) || content[end] == '_'))
// 		return (NULL);
// 	while (content[end] != '\0' && (ft_isalnum(content[end])
// 			|| content[end] == '_' || content[end] == '/'
// 			|| content[end] == '.'))
// 		end++;
// 	var_path = ft_substr(content, (unsigned int)extr, (size_t)(end - extr));
// 	*start = end;
// 	return (var_path);
// }

// static char	*var_expand(const char *content, int *i, char *result, t_env *env)
// {
// 	char	*var;
// 	char	*expanded;
// 	char	*new_result;

// 	var = var_extract(content, i);
// 	expanded = expand_dollar_sign(var, env);
// 	new_result = ft_strjoin(result, expanded);
// 	free(result);
// 	free(expanded);
// 	free(var);
// 	return (new_result);
// }

// static char	*exit_status_expand(char *result, t_exec *exec)
// {
// 	char	*temp;
// 	char	*exit_status;

// 	temp = result;
// 	exit_status = ft_itoa(exec->exit_status);
// 	result = ft_strjoin(result, exit_status);
// 	free(temp);
// 	free(exit_status);
// 	return (result);
// }

// static char	*char_join(char *result, char c)
// {
// 	char	*temp;
// 	char	*new_result;

// 	temp = (char *)ft_calloc(2, sizeof(char));
// 	if (!temp)
// 		return (result);
// 	temp[0] = c;
// 	temp[1] = '\0';
// 	new_result = ft_strjoin(result, temp);
// 	free(result);
// 	free(temp);
// 	return (new_result);
// }

// char	*expand_double_quote(const char *content, t_env *env, t_exec *exec)
// {
// 	char	*result;
// 	int		i;

// 	result = (char *)ft_calloc(1, sizeof(char));
// 	if (!result)
// 		return (NULL); //TODO handle malloc error or maybe just don't handle it so this shit is 25lines?????
// 	i = 0;
// 	while (content[i])
// 	{
// 		if (content[i] == '$' && content [i + 1] == '?')
// 		{
// 			i += 2;
// 			result = exit_status_expand(result, exec);
// 		}
// 		else if (content[i] == '$')
// 		{
// 			i++;
// 			if ((ft_isalpha(content[i]) || content[i] == '_'))
// 				result = var_expand(content, &i, result, env);
// 			else
// 				result = char_join(result, '$');
// 		}
// 		else
// 			result = char_join(result, content[i++]);
// 	}
// 	return (result);
// }
