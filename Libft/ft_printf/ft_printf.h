/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:18:41 by mott              #+#    #+#             */
/*   Updated: 2024/02/18 16:40:57 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>

typedef struct s_flags
{
	bool	left_adjusted;
	bool	plus_sign;
	bool	space_sign;
	bool	alternate_form;
	bool	zero_padded;
	int		field_width;
	int		precision;
}	t_flags;

int			ft_printf(const char *format, ...);
int			ft_putchar(int c);
int			ft_putnstr(char *str, int n);
int			ft_putnbr10(long n);
int			ft_putnbr16(unsigned long n, char xp);

int			ft_read_conversion(va_list ap, const char **format);
t_flags		ft_init_flags(va_list ap, const char **format);
t_flags		ft_read_flags(const char **format, t_flags *flags);
t_flags		ft_read_width(va_list ap, const char **format, t_flags *flags);
t_flags		ft_read_precision(va_list ap, const char **format, t_flags *flags);

int			ft_process_char(int c, t_flags *flags);
int			ft_process_str(char *str, t_flags *flags);
int			ft_process_nbr10(long nbr, t_flags *flags);
int			ft_process_nbr16(long nbr, t_flags *flags, char xp);
int			ft_set_sign(long *nbr, t_flags *flags);

bool		ft_is_digit(int c);
int			pf_toupper(int c);
int			ft_strnlen(const char *str, size_t n);
int			ft_nbrlen(unsigned long nbr, unsigned long base);
int			ft_fill(int n, char c);

#endif
