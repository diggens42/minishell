/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:08:58 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/22 13:43:17 by mott             ###   ########.fr       */
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

static void	handle_command_quotes(bool *quotes, char *quote_type, char current)
{
	if (current == '"' || current == '\'')
	{
		if (!(*quotes))
		{
			*quotes = true;
			*quote_type = current;
		}
		else if (*quote_type == current)
		{
			*quotes = false;
			*quote_type = '\'';
		}
	}
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
	else
		return (get_command_len(cmd_line));
	return (len);
}
