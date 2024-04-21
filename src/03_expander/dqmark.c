/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dqmark.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:30:46 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/21 18:41:45 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_dollar_qmark(t_mini *mini, char *content)
{
	char	*pos;
	char	*before_dqmark;
	char	*after_dqmark;
	char	*newstr;
	int		quote_state;

	quote_state = 0;
	newstr = ft_strdup(content);
	pos = newstr;
	while (*pos)
	{
		quote_state = set_quote_state(quote_state, *pos);
		if (*pos == '$' && *(pos + 1) == '?' && quote_state == 0)
		{
			before_dqmark = ft_substr(newstr, 0, pos - newstr);
			after_dqmark = ft_strjoin_free(ft_itoa(mini->exit_status), pos + 2);
			free(newstr);
			newstr = ft_strjoin(before_dqmark, after_dqmark);
			pos++;
			free(before_dqmark);
			free(after_dqmark);
		}
		pos++;
	}
	return (newstr);
}

char	*expand_exit_status(t_mini *mini, char *result)
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
