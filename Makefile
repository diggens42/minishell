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
		./src/lexer/tokenizer.c \
		./src/lexer/token_ops.c \
		./src/lexer/token_length.c \
		./src/lexer/token_length2.c \
		./src/lexer/token_type.c \
		./src/lexer/syntax_operators.c \
		./src/lexer/syntax_unclosed.c \
		\
		./src/expander/expand_token.c \
		./src/expander/expand_command.c \
		./src/expander/expand_command2.c \
		./src/expander/expand_dquotes.c \
		./src/expander/expand_dollar.c \
		./src/expander/expand_wildcard.c \
		./src/expander/expand_wildcard2.c \
		./src/expander/expand_utils.c \
		\
		./src/parser/ast_parser.c \
		./src/parser/ast_parser2.c \
		./src/parser/ast_utils.c \
		\
		./src/builtin/cd.c \
		./src/builtin/echo.c \
		./src/builtin/env.c \
		./src/builtin/exit.c \
		./src/builtin/export.c \
		./src/builtin/pwd.c \
		./src/builtin/unset.c \
		./src/builtin/utils.c \
		\
		./src/executor/exec_heredoc.c \
		./src/executor/exec_main.c \
		./src/executor/exec_path.c \
		./src/executor/exec_pipe.c \
		./src/executor/exec_redir.c \
		./src/executor/exec_utils_1.c \
		./src/executor/exec_utils_2.c \
		\
		./src/utils/debug.c \
		./src/utils/env.c \
		./src/utils/exit.c \
		./src/utils/free.c \
		./src/utils/signals.c \
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
