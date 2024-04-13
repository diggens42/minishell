/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:57:08 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/13 16:28:28 by fwahl            ###   ########.fr       */
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
	static char		*buffer[123];
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc((sizeof(char) * (BUFFER_SIZE + 1)));
		if (!buffer[fd])
			return (NULL);
		ft_memset(buffer[fd], 0, BUFFER_SIZE + 1);
	}
	buffer[fd] = read_to_buff(fd, buffer[fd]);
	if (buffer[fd] == NULL || (buffer[fd][0] == '\0'))
	{
		if (buffer[fd])
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
		return (NULL);
	}
	next_line = get_line_from_buff(buffer[fd]);
	buffer[fd] = get_remain(buffer[fd]);
	return (next_line);
}
