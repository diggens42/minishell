/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:21:52 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/11 19:22:47 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*extract_var_name(const char *content)
{
	char	*slash_pos;
	char	*var_name;
	size_t	var_name_len;
	
	slash_pos = ft_strchr(content, '/');
	if (slash_pos != NULL)
		var_name_len = slash_pos - content - 1;
	else
		var_name_len = ft_strlen(content) - 1;
	var_name = (char *)malloc(var_name_len + 1);
	if (!var_name)
		ft_exit();//TODO malloc error
	if (var_name)
		ft_strlcpy(var_name, content + 1, var_name_len + 1);
	return (var_name);
}

static char	*construct_new_content(const char *var_value, const char *content)
{
	char	*slash_pos;
	char	*new_content;
	size_t	var_value_len;
	size_t	after_slash_len;
	size_t	new_content_len;

	slash_pos = ft_strchr(content, '/');
	var_value_len = ft_strlen(var_value);
	after_slash_len = 0;
	if (slash_pos != NULL)
		after_slash_len = ft_strlen(slash_pos);
	new_content_len = var_value_len + after_slash_len;
	new_content = (char *)malloc(new_content_len + 1);
	if (!new_content)
		ft_exit(); //TODO malloc error
	if (new_content)
	{
		ft_memcpy(new_content, var_value, var_value_len);
		if (slash_pos)
			ft_memcpy(new_content + var_value_len, slash_pos, after_slash_len);
		new_content[new_content_len] = '\0';
	}
	return (new_content);
}

char	*expand_content(const char *content, t_env *env)
{
	char	*var_name;
	char	*var_value;
	char	*new_content;

	var_name = extract_var_name(content);
	var_value = ft_getenv(var_name, env);
	if (!var_value)
		var_value = "";
	new_content = construct_new_content(var_value, content);
	free(var_name);
	return(new_content);
}
