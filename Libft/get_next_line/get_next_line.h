/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:41:24 by mott              #+#    #+#             */
/*   Updated: 2024/02/12 17:51:37 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

// get_next_line.c
char	*get_next_line(int fd);
char	*ft_read_line(int fd, char *temp);
char	*ft_create_current_line(char *temp);
char	*ft_create_next_line(char *temp);

// get_next_line_utils.c
size_t	gnl_strlen(const char *str);
char	*gnl_strchr(const char *str, int c);
char	*gnl_strjoin(const char *str1, const char *str2);
char	*gnl_substr(const char *str, size_t start, size_t n);

#endif
