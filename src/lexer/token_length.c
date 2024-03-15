/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:08:58 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 15:54:24 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_quote(char *user_input)
{
	int		len;
	char	quote_type;

	quote_type = user_input[0];
	len = 1;
	while (user_input[len] != '\0' && user_input[len] != quote_type)
		len++;
	if (user_input[len] == quote_type)
		len++;
	return (len);
}

static int	is_dollar_sign(char *user_input)
{
	int		len;
	char	c;

	len = 1;
	if (user_input[1] == '?' || user_input[1] == '$')
		return (2);
	while (user_input[len] != '\0' && !ft_isspace(user_input[len]))
	{
		c = user_input[len];
		if (!ft_isalnum(c) || c == '_' || c == '/' || c == '.')
			break ;
		len++;
	}
	return (len);
}

static int	is_single_special_char(char c)
{
	return (ft_strchr("|<>()", c) != NULL);
}

static int	is_double_special_char(char *user_input)
{
	const char	*symbols[] = {"&&", "||", "<<", ">>", NULL};
	int			len;

	len = 0;
	while (symbols[len] != NULL)
	{
		if (ft_strncmp(user_input, symbols[len], ft_strlen(symbols[len])) == 0)
			return (ft_strlen(symbols[len]));
		len++;
	}
	return (0);
}

int	set_token_length(char *user_input)
{
	int	len;

	len = is_double_special_char(user_input);
	if (len > 0)
		return (len);
	if (is_single_special_char(user_input[0]))
		return (1);
	if (user_input[0] == '"' || user_input[0] == '\'')
		return (is_quote(user_input));
	if (user_input[0] == '$')
		return (is_dollar_sign(user_input));
	while (user_input[len] != '\0' && !ft_isspace(user_input[len])
		&& !is_single_special_char(user_input[len]))
		len++;
	return (len);
}
