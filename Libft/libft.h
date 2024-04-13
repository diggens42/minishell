/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:04:53 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/13 16:58:00 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/select.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Character checking functions
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_issign(int c);
// Memory manipulation functions
void			*ft_realloc(void *ptr, size_t new_size);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *ptr, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_free_strarray(char **str);
// String manipulation and checking functions
char			**ft_strarray_append(char **array, char *str);
int				ft_strarray_len(char **array);
size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlcat(char *dest, const char *src, size_t dest_size);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *str1, size_t n);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_free(char *str1, const char *str2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strrstr(const char *haystack, const char *needle);
void			ft_strrev(char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strtok(char	*str, const char *delimiter);
size_t			ft_strspn(const char *str, const char *charset);
size_t			ft_strcspn(const char *str, const char *charset);
char			**ft_split(char const *s, char c);
// Character conversion functions
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_atoi(const char *s);
long			ft_atol(const char *s);
double			ft_atodbl(const char *s);
char			*ft_itoa(int n);
// Memory allocation
void			*ft_calloc(size_t count, size_t size);
// IO related functions
int				ft_printf(const char *f, ...);
char			*get_next_line(int fd);
void			ft_putbase(unsigned long num, int base, int upper);
void			ft_putint(long num);
void			ft_putptr(unsigned long num);
void			ft_putchar(char c);
void			ft_putstr(char *str);
void			ft_putnbr_fd(int n, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);

// Linked list related functions
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

//printf
int				ft_printf(const char *string, ...);
int				ft_check_format(const char format, va_list *ap);
int				ft_put_chr_len(int c);
int				ft_put_str_len(char *str);
int				ft_put_nbr_len(long num);
int				ft_put_ptr_len(unsigned long num);
unsigned long	ft_put_base_len(unsigned long num, int base, int upper);


#endif
