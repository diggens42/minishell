/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:36:04 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/17 21:30:15 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static char	*get_line_from_buff(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (i > j++)
		line[j - 1] = buffer[j - 1];
	line[i] = '\0';
	return (line);
}

static char	*read_to_buff(int fd, char *buffer)
{
	size_t	nbytes;
	char	read_string[BUFFER_SIZE + 1];
	char	*temp;

	if (read(fd, NULL, 0) == -1)
	{
		free(buffer);
		return (NULL);
	}
	while (1)
	{
		nbytes = read(fd, read_string, BUFFER_SIZE);
		if (nbytes == 0)
			return (buffer);
		if (nbytes <= BUFFER_SIZE)
			read_string[nbytes] = '\0';
		temp = ft_strjoin(buffer, read_string);
		if (temp == NULL)
			return (NULL);
		free(buffer);
		buffer = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (buffer);
}

static char	*get_remain(char *buffer)
{
	char	*remain;
	char	*buff_ptr;
	char	*dest;

	buff_ptr = buffer;
	while (*buff_ptr && *buff_ptr != '\n')
		buff_ptr++;
	if (*buff_ptr == '\0')
	{
		free(buffer);
		return (NULL);
	}
	remain = malloc(sizeof(char) * (ft_strlen(buff_ptr) + 1));
	buff_ptr++;
	dest = remain;
	if (!remain)
		return (NULL);
	while (*buff_ptr != 0)
		*dest++ = *buff_ptr++;
	*dest = '\0';
	free(buffer);
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}
	if (!buffer)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (NULL);
	}
	buffer = read_to_buff(fd, buffer);
	if (buffer == NULL || (buffer[0] == '\0'))
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}
	next_line = get_line_from_buff(buffer);
	buffer = get_remain(buffer);
	return (next_line);
}
