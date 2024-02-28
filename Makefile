# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 17:46:19 by mott              #+#    #+#              #
#    Updated: 2024/02/27 17:49:55 by mott             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRCS = ./src/

OBJS = $(SRCS:.c=.o)

HEADER = ./include/minishell.h

LIBFT = ./Libft/libft.a

X = "\033[0m"
R = "\033[31m"
G = "\033[32m"
Y = "\033[33m"
B = "\033[34m"

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@
	@echo $(B)$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@$(X)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(Y)$(CC) $(CFLAGS) -c $< -o $@$(X)

$(LIBFT):
	@$(MAKE) -C ./Libft

clean:
	@rm -f $(OBJS)
	@echo $(R)rm -f $(OBJS)$(X)
	@$(MAKE) clean -C ./Libft

fclean: clean
	@rm -f $(NAME)
	@echo $(R)rm -f $(NAME)$(X)
	@$(MAKE) fclean -C ./Libft

re: fclean all

.PHONY: all clean fclean re

# https://www.gnu.org/software/make/manual/make.html
# $@ automatic variable that holds the name of the target
# $< automatic variable that holds the name of the first prerequisite
# $^ automatic variable that holds the names of all the prerequisites
