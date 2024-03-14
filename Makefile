# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 17:46:19 by mott              #+#    #+#              #
#    Updated: 2024/03/03 17:43:53 by mott             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I include -I /usr/local/include/readline
NAME = minishell

SRCS =	./src/minishell.c \
		\
		./src/lexer/process_dquotes.c \
		./src/lexer/process_expand.c \
		./src/lexer/process_squotes.c \
		./src/lexer/process_token.c \
		./src/lexer/token_length.c \
		./src/lexer/token_ops.c \
		./src/lexer/token_type.c \
		./src/lexer/tokenizer.c \
		\
		./src/parser/ast_simple.c\
		./src/parser/ast_parser.c\
		./src/parser/ast_cmd.c\
		./src/parser/ast_pipe.c\
		./src/parser/ast_logical.c\
		./src/parser/ast_parenthesis.c\
		./src/parser/ast_redirect.c\
		\
		./src/builtin/cd.c \
		./src/builtin/echo.c \
		./src/builtin/env.c \
		./src/builtin/export.c \
		./src/builtin/pwd.c \
		./src/builtin/unset.c \
		\
		./src/executor/exec_main.c \
		./src/executor/exec_path.c \
		./src/executor/exec_utils.c \
		./src/executor/exec_utils2.c \
		\
		./src/utils/debug_tokenizer.c \
		./src/utils/debug.c \
		./src/utils/exit.c \
		./src/utils/free.c \
		./src/utils/init_env.c \
		./src/utils/utils.c

OBJS = $(SRCS:.c=.o)

LIBFT = ./Libft/libft.a

X = "\033[0m"
R = "\033[31m"
G = "\033[32m"
Y = "\033[33m"
B = "\033[34m"

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline  -o $@
	@echo $(B)$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@$(X)

%.o: %.c
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
