
CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a
HEADER = libft.h

SRCS =	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c \
		\
		ft_atoi.c ft_atol.c ft_atodbl.c ft_itoa.c ft_tolower.c ft_toupper.c \
		\
		ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
		\
		ft_realloc.c ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_free_strarray.c \
		\
		get_next_line.c get_next_line_bonus.c ft_printf.c put_chars.c put_numbers.c \
		ft_putbase.c ft_putchar_fd.c ft_putchar.c ft_putendl_fd.c ft_putint.c ft_putnbr_fd.c ft_putptr.c ft_putstr_fd.c ft_putstr.c \
		\
		ft_strarray_append.c ft_strarray_len.c ft_split.c ft_strdup.c ft_strndup.c ft_striteri.c ft_strjoin.c ft_strjoin_free.c \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strcmp.c ft_strncmp.c ft_strnstr.c ft_strchr.c ft_strrchr.c ft_strstr.c \
		ft_strrstr.c ft_strrev.c ft_strtrim.c ft_substr.c ft_strtok.c ft_strspn.c ft_strcspn.c

vpath %.c bool conversion linked_list mem output/get_next_line output/ft_printf output str
vpath %.h .

OBJDIR = obj
OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SRCS)))

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	$(foreach src,$(SRCS),mkdir -p $(OBJDIR)/$(dir $(src));)

$(OBJDIR)/%.o: %.c $(HEADER) | $(OBJDIR)
	@mkdir -p $(@D)
	@echo "$(YELLOW)Libft is compiling...$(RESET)"
	@$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@echo "$(GREEN)Libft compilation finished$(RESET)"

clean:
	@echo "$(RED)Removing output files$(RESET)"
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

# > /dev/null 2>&1
