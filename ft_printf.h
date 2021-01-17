/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoki <saoki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 07:52:39 by saoki             #+#    #+#             */
/*   Updated: 2021/01/17 09:34:25 by saoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

typedef enum	e_flag
{
	FLAG_SHARP = 0,
	FLAG_ZERO = 1,
	FLAG_MINUS = 2,
	FLAG_SPACE = 3,
	FLAG_PLUS = 4
}				t_flag;

typedef enum	e_spec
{
	SPEC_D = 0,
	SPEC_I = 1,
	SPEC_U = 2,
	SPEC_SX = 3,
	SPEC_LX = 4,
	SPEC_C = 5,
	SPEC_S = 6,
	SPEC_P = 7,
	SPEC_PER = 8
}				t_spec;

typedef struct	s_data_flag
{
	int	flag[5];
	int	field;
	int	precision;
	int	specifier;
	int	sum_printed_len;
	int	printed_len;
}				t_data_flag;

int				ft_printf(const char *fmt, ...);
void			print_ordinary_str(const char **start, const char **fmt,
				int *n);
void			print_specifier_str(const char **start, const char **fmt, int *n
				, va_list *ap);
void			initialize_data(t_data_flag *data, int n);
int				printf_strchr(const char *s, char c);
int				get_field(const char **fmt, va_list *ap, t_data_flag *data);
int				get_precision(const char **fmt, va_list *ap);
int				ft_isdigit(int c);
int				print_data(const char **start, const char **fmt, va_list *ap,
				t_data_flag *data);
int				print_non_specifier(const char **start, const char **fmt,
				t_data_flag *data);
void			print_int(va_list *ap, t_data_flag *data);
void			print_unsigned(va_list *ap, t_data_flag *data);
void			print_char(va_list *ap, t_data_flag *data);
void			print_string(va_list *ap, t_data_flag *data);
void			print_pointer(va_list *ap, t_data_flag *data);
void			print_persent(t_data_flag *data);
void			printf_putchar(char c, int num);
void			put_minus(long long num);
void			print_digit_re(unsigned long long n, char *base,
				unsigned int size);
void			putnbr_diux(unsigned long long num, t_data_flag data);
void			get_putlen_di(t_data_flag *data, long long num);
int				get_digit_di(long long num);
void			get_putlen_ux(t_data_flag *data, unsigned long long num);
int				get_digit_ux(unsigned long long num, t_data_flag data);
void			print_char(va_list *ap, t_data_flag *data);
void			print_string(va_list *ap, t_data_flag *data);
int				set_print_string(va_list *ap, t_data_flag *data, char **s);
int				ft_strlen(const char *str);
int				print_null(t_data_flag *data, char **s);
void			pointer_null(t_data_flag *data);

#endif
