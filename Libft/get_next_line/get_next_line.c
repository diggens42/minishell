/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:39:39 by mott              #+#    #+#             */
/*   Updated: 2024/02/10 13:59:04 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*next_line;
	char		*current_line;
	char		*temp;

	if (fd < 0)
	{
		if (next_line != NULL)
			free(next_line);
		return (NULL);
	}
	temp = ft_read_line(fd, next_line);
	current_line = ft_create_current_line(temp);
	next_line = ft_create_next_line(temp);
	return (free(temp), current_line);
}

char	*ft_read_line(int fd, char *temp)
{
	char		*buffer;
	char		*swap;
	ssize_t		nbytes;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	while (gnl_strchr(temp, '\n') == NULL)
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes == -1)
		{
			if (temp != NULL)
				free(temp);
			return (free(buffer), NULL);
		}
		else if (nbytes == 0)
			break ;
		buffer[nbytes] = '\0';
		swap = temp;
		temp = gnl_strjoin(swap, buffer);
		free(swap);
	}
	return (free(buffer), temp);
}

char	*ft_create_current_line(char *temp)
{
	char	*current_line;
	size_t	start;
	size_t	n;

	start = 0;
	if (gnl_strchr(temp, '\n') != NULL)
		n = gnl_strchr(temp, '\n') - temp + 1;
	else
		n = gnl_strlen(temp);
	current_line = gnl_substr(temp, start, n);
	return (current_line);
}

char	*ft_create_next_line(char *temp)
{
	char	*next_line;
	size_t	start;
	size_t	n;

	if (gnl_strchr(temp, '\n') != NULL)
		start = gnl_strchr(temp, '\n') - temp + 1;
	else
		return (NULL);
	n = gnl_strlen(temp) - start;
	if (n == 0)
		return (NULL);
	next_line = gnl_substr(temp, start, n);
	return (next_line);
}
