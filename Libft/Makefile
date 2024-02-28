# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/13 13:29:46 by mott              #+#    #+#              #
#    Updated: 2024/02/16 15:56:45 by mott             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRCS = ft_atoi.c \
       ft_bzero.c \
       ft_calloc.c \
       ft_isalnum.c \
       ft_isalpha.c \
       ft_isascii.c \
       ft_isdigit.c \
       ft_isprint.c \
       ft_isspace.c \
       ft_itoa.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_memset.c \
       ft_putchar_fd.c \
       ft_putendl_fd.c \
       ft_putnbr_fd.c \
       ft_putstr_fd.c \
       ft_split.c \
       ft_strchr.c \
       ft_strdup.c \
       ft_striteri.c \
       ft_strjoin.c \
       ft_strlcat.c \
       ft_strlcpy.c \
       ft_strlen.c \
       ft_strmapi.c \
       ft_strncmp.c \
       ft_strnstr.c \
       ft_strrchr.c \
       ft_strtrim.c \
       ft_substr.c \
       ft_tolower.c \
       ft_toupper.c \
       ft_lstadd_back.c \
       ft_lstadd_front.c \
       ft_lstclear.c \
       ft_lstdelone.c \
       ft_lstiter.c \
       ft_lstlast.c \
       ft_lstmap.c \
       ft_lstnew.c \
       ft_lstsize.c \
       ft_printf/ft_printf.c \
       ft_printf/ft_printf_flags.c \
       ft_printf/ft_printf_process.c \
       ft_printf/ft_printf_utils.c \
       get_next_line/get_next_line.c \
       get_next_line/get_next_line_utils.c \
       # get_next_line/get_next_line_bonus.c \
       # get_next_line/get_next_line_utils_bonus.c

OBJS = $(SRCS:.c=.o)

HEADER = libft.h

X = "\033[0m"
R = "\033[31m"
G = "\033[32m"
Y = "\033[33m"
B = "\033[34m"

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo $(B)ar rcs $(NAME) $(OBJS)$(X)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(Y)$(CC) $(CFLAGS) -c $< -o $@$(X)

clean:
	@rm -f $(OBJS)
	@echo $(R)rm -f $(OBJS)$(X)

fclean: clean
	@rm -f $(NAME)
	@echo $(R)rm -f $(NAME)$(X)

re: fclean all

.PHONY: all clean fclean re

# https://www.gnu.org/software/make/manual/make.html
# $@ automatic variable that holds the name of the target
# $< automatic variable that holds the name of the first prerequisite
# $^ automatic variable that holds the names of all the prerequisites
