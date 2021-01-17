/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoki <saoki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:14:02 by saoki             #+#    #+#             */
/*   Updated: 2021/01/14 20:32:49 by saoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_char(va_list *ap, t_data_flag *data)
{
	char	c;

	c = (char)va_arg(*ap, int);
	data->printed_len = 1;
	if (data->field <= data->printed_len)
		data->field = 0;
	else
		data->field -= data->printed_len;
	if (!data->flag[FLAG_MINUS])
		printf_putchar(' ', data->field);
	printf_putchar(c, 1);
	if (data->flag[FLAG_MINUS])
		printf_putchar(' ', data->field);
}

void		print_string(va_list *ap, t_data_flag *data)
{
	char	*s;

	if (data->precision == -1)
		data->precision = INT_MAX;
	set_print_string(ap, data, &s);
	if (data->field <= data->printed_len)
		data->field = 0;
	else
		data->field -= data->printed_len;
	if (!data->flag[FLAG_MINUS])
	{
		if (data->flag[FLAG_ZERO])
			printf_putchar('0', data->field);
		else
			printf_putchar(' ', data->field);
	}
	write(1, s, data->printed_len);
	if (data->flag[FLAG_MINUS])
		printf_putchar(' ', data->field);
}

int			set_print_string(va_list *ap, t_data_flag *data, char **s)
{
	int		n;

	if (ap == NULL)
		return (print_null(data, s));
	*s = (char *)va_arg(*ap, char *);
	if (*s == NULL)
		return (print_null(data, s));
	n = ft_strlen(*s);
	if (n <= data->precision && data->precision != INT_MAX)
	{
		data->printed_len = n;
		data->precision -= n;
	}
	else if (n <= data->precision && data->precision == INT_MAX)
	{
		data->printed_len = n;
		data->precision = 0;
	}
	else if (n > data->precision)
	{
		data->printed_len = data->precision;
		data->precision = 0;
	}
	return (n);
}

int			print_null(t_data_flag *data, char **s)
{
	*s = "(null)";
	data->printed_len = 6;
	if (data->printed_len > data->precision)
		data->printed_len = data->precision;
	return (0);
}
