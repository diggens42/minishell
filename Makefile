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
		./src/01_lexer/_lexer.c \
		./src/01_lexer/token_ops.c \
		./src/01_lexer/token_length.c \
		./src/01_lexer/token_length2.c \
		./src/01_lexer/token_type.c \
		./src/01_lexer/syntax_operators.c \
		./src/01_lexer/syntax_unclosed.c \
		\
		./src/02_parser/_parser.c \
		./src/02_parser/ast_redirect.c \
		./src/02_parser/utils.c \
		\
		./src/03_expander/_expander.c \
		./src/03_expander/cmd.c \
		./src/03_expander/dqmark.c \
		./src/03_expander/dquotes.c \
		./src/03_expander/dollar.c \
		./src/03_expander/glob.c \
		./src/03_expander/utils.c \
		\
		./src/04_executor/_executor.c \
		./src/04_executor/heredoc.c \
		./src/04_executor/path.c \
		./src/04_executor/pipe.c \
		./src/04_executor/redir.c \
		./src/04_executor/utils_1.c \
		./src/04_executor/utils_2.c \
		./src/04_executor/builtin/cd.c \
		./src/04_executor/builtin/echo.c \
		./src/04_executor/builtin/env.c \
		./src/04_executor/builtin/env2.c \
		./src/04_executor/builtin/exit.c \
		./src/04_executor/builtin/export.c \
		./src/04_executor/builtin/export2.c \
		./src/04_executor/builtin/pwd.c \
		./src/04_executor/builtin/unset.c \
		\
		./src/utils/env.c \
		./src/utils/exit.c \
		./src/utils/free.c \
		./src/utils/utils.c \
		\
		./src/utils/signals/child.c \
		./src/utils/signals/parent.c

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $@
	@echo "$(GREEN)Minishell compilation finished$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C ./libft

clean:
	@echo "$(RED)Cleaning minishell output files$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) clean -C ./libft

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C ./libft

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re

# https://www.gnu.org/software/make/manual/make.html
# $@ automatic variable that holds the name of the target
# $< automatic variable that holds the name of the first prerequisite
# $^ automatic variable that holds the names of all the prerequisites
