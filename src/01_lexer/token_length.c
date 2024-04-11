/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:08:58 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/10 19:35:55 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_quote_len(char *user_input)
{
	int		len;
	char	quote_type;

	quote_type = user_input[0];
	len = 1;
	while (user_input[len] != '\0' && user_input[len] != quote_type)
		len++;
	if (user_input[len] == quote_type)
		len++;
	while (!ft_isspace(user_input[len]) && !get_single_char_len(user_input[len])
		&& user_input[len] != '\0')
		len++;
	return (len);
}

static int	get_double_char_len(char *user_input)
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

static int	get_dollar_len(char *user_input)
{
	int		len;

	len = 1;
	if (user_input[1] == '?')
	{
		if (user_input[2] != '\0' && !ft_isspace(user_input[2])
			&& !get_single_char_len(user_input[2]))
		{
			len = 2;
			while (user_input[len] != '\0' && !ft_isspace(user_input[len])
				&& !get_single_char_len(user_input[len]))
				len++;
		}
		else
			return (2);
	}
	else
	{
		while (user_input[len] != '\0' && !ft_isspace(user_input[len])
			&& !get_single_char_len(user_input[len]))
		{
			if (!ft_isalnum(user_input[len]) && user_input[len] != '_'
				&& user_input[len] != '/' && user_input[len] != '.')
				break ;
			len++;
		}
	}
	return (len);
}

static int	get_command_len(char *user_input)
{
	int		len;
	bool	quotes;
	char	quote_type;

	len = 0;
	quotes = false;
	quote_type = '\0';
	while (user_input[len] != '\0')
	{
		handle_command_quotes(&quotes, &quote_type, user_input[len]);
		if (!quotes && (ft_isspace(user_input[len])
				|| get_single_char_len(user_input[len])))
			break ;
		len++;
	}
	return (len);
}

int	set_token_length(char *user_input)
{
	int	len;

	len = get_double_char_len(user_input);
	if (len > 0)
		return (len);
	else if (get_single_char_len(user_input[0]))
		return (1);
	else if (user_input[0] == '"' || user_input[0] == '\'')
		return (get_quote_len(user_input));
	else if (user_input[0] == '$')
		return (get_dollar_len(user_input));
	else
		return (get_command_len(user_input));
	return (len);
}
