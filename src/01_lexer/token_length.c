/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:08:58 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/17 19:16:31 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_quote_len(char *cmd_line)
{
	int		len;
	char	quote_type;

	quote_type = cmd_line[0];
	len = 1;
	while (cmd_line[len] != '\0' && cmd_line[len] != quote_type)
		len++;
	if (cmd_line[len] == quote_type)
		len++;
	while (!ft_isspace(cmd_line[len]) && !get_single_char_len(cmd_line[len])
		&& cmd_line[len] != '\0')
		len++;
	return (len);
}

static int	get_double_char_len(char *cmd_line)
{
	const char	*symbols[] = {"&&", "||", "<<", ">>", NULL};
	int			len;

	len = 0;
	while (symbols[len] != NULL)
	{
		if (ft_strncmp(cmd_line, symbols[len], ft_strlen(symbols[len])) == 0)
			return (ft_strlen(symbols[len]));
		len++;
	}
	return (0);
}

static int	get_dollar_len(char *cmd_line)
{
	int		len;

	len = 1;
	if (cmd_line[1] == '?')
	{
		if (cmd_line[2] != '\0' && !ft_isspace(cmd_line[2])
			&& !get_single_char_len(cmd_line[2]))
		{
			len = 2;
			while (cmd_line[len] != '\0' && !ft_isspace(cmd_line[len])
				&& !get_single_char_len(cmd_line[len]))
				len++;
		}
		else
			return (2);
	}
	else
	{
		while (cmd_line[len] != '\0' && !ft_isspace(cmd_line[len])
			&& !get_single_char_len(cmd_line[len]))
		{
			if (!ft_isalnum(cmd_line[len]) && cmd_line[len] != '_'
				&& cmd_line[len] != '/' && cmd_line[len] != '.')
				break ;
			len++;
		}
	}
	return (len);
}

static int	get_command_len(char *cmd_line)
{
	int		len;
	bool	quotes;
	char	quote_type;

	len = 0;
	quotes = false;
	quote_type = '\0';
	while (cmd_line[len] != '\0')
	{
		handle_command_quotes(&quotes, &quote_type, cmd_line[len]);
		if (!quotes && (ft_isspace(cmd_line[len])
				|| get_single_char_len(cmd_line[len])))
			break ;
		len++;
	}
	return (len);
}

int	set_token_length(char *cmd_line)
{
	int	len;

	len = get_double_char_len(cmd_line);
	if (len > 0)
		return (len);
	else if (get_single_char_len(cmd_line[0]))
		return (1);
	else if (cmd_line[0] == '"' || cmd_line[0] == '\'')
		return (get_quote_len(cmd_line));
	else if (cmd_line[0] == '$')
		return (get_dollar_len(cmd_line));
	else
		return (get_command_len(cmd_line));
	return (len);
}
