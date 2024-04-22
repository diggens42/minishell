/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:30:50 by mott              #+#    #+#             */
/*   Updated: 2024/04/22 19:32:11 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static char	*gn_read_line(int fd, char *temp)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*to_free;
	int		nbytes;

	while (gn_strchr(temp, '\n') == NULL)
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes == -1)
		{
			if (temp != NULL)
				free(temp);
			return (NULL);
		}
		else if (nbytes == 0)
			break ;
		buffer[nbytes] = '\0';
		to_free = temp;
		temp = gn_strjoin(temp, buffer);
		free(to_free);
	}
	return (temp);
}

static char	*gn_current_line(char *temp)
{
	char	*current_line;
	int		start;
	int		n;

	start = 0;
	if (gn_strchr(temp, '\n') != NULL)
		n = gn_strchr(temp, '\n') - temp + 1;
	else
		n = gn_strlen(temp);
	current_line = gn_substr(temp, start, n);
	return (current_line);
}

static char	*gn_next_line(char *temp)
{
	char	*next_line;
	int		start;
	int		n;

	if (gn_strchr(temp, '\n') != NULL)
		start = gn_strchr(temp, '\n') - temp + 1;
	else
		return (NULL);
	n = gn_strlen(temp) - start;
	if (n == 0)
		return (NULL);
	next_line = gn_substr(temp, start, n);
	return (next_line);
}

char	*get_next_line(int fd)
{
	char		*temp;
	char		*current_line;
	static char	*next_line;

	if (fd < 0)
		return (NULL);
	temp = gn_read_line(fd, next_line);
	current_line = gn_current_line(temp);
	next_line = gn_next_line(temp);
	free(temp);
	return (current_line);
}
