/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:05:24 by mott              #+#    #+#             */
/*   Updated: 2024/02/12 17:51:42 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

// get_next_line_bonus.c
char	*get_next_line(int fd);
char	*ft_read_line(int fd, char *temp);
char	*ft_create_current_line(char *temp);
char	*ft_create_next_line(char *temp);

// get_next_line_utils_bonus.c
size_t	gnl_strlen(const char *str);
char	*gnl_strchr(const char *str, int c);
char	*gnl_strjoin(const char *str1, const char *str2);
char	*gnl_substr(const char *str, size_t start, size_t n);

#endif
