/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoki <saoki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 08:45:13 by saoki             #+#    #+#             */
/*   Updated: 2021/01/14 20:24:35 by saoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				get_field(const char **fmt, va_list *ap, t_data_flag *data)
{
	int		num;

	num = 0;
	if (**fmt == '*')
	{
		num = va_arg(*ap, int);
		if (num < 0)
		{
			num *= -1;
			data->flag[FLAG_MINUS] = 1;
		}
		(*fmt)++;
	}
	else if (ft_isdigit(**fmt))
	{
		while (ft_isdigit(**fmt))
			num = num * 10 + (*((*fmt)++) - '0');
	}
	return (num);
}

int				get_precision(const char **fmt, va_list *ap)
{
	int		num;

	num = -1;
	if (**fmt == '*')
	{
		num = va_arg(*ap, int);
		if (num < 0)
			num = -1;
		(*fmt)++;
	}
	else if (ft_isdigit(**fmt))
	{
		num = 0;
		while (ft_isdigit(**fmt))
			num = num * 10 + (*((*fmt)++) - '0');
	}
	else if (!ft_isdigit(**fmt))
		num = 0;
	return (num);
}

void			print_ordinary_str(const char **start, const char **fmt, int *n)
{
	while (**fmt != '%' && **fmt)
		(*fmt)++;
	write(1, *start, *fmt - *start);
	*n += *fmt - *start;
}

void			print_specifier_str(const char **start,
		const char **fmt, int *n, va_list *ap)
{
	int			num;
	t_data_flag	data;

	(*fmt)++;
	initialize_data(&data, *n);
	while ((num = printf_strchr("#0- +", **fmt)) >= 0)
	{
		data.flag[num] = 1;
		(*fmt)++;
	}
	data.field = get_field(fmt, ap, &data);
	if (**fmt == '.')
	{
		(*fmt)++;
		data.precision = get_precision(fmt, ap);
	}
	data.specifier = printf_strchr("diuxXcsp%", **fmt);
	num = print_data(start, fmt, ap, &data);
	*n = num;
}

int				ft_printf(const char *fmt, ...)
{
	int			n;
	va_list		ap;
	const char	*start;

	n = 0;
	va_start(ap, fmt);
	while (n >= 0 && *fmt)
	{
		start = fmt;
		if (*start != '%')
			print_ordinary_str(&start, &fmt, &n);
		else
			print_specifier_str(&start, &fmt, &n, &ap);
	}
	va_end(ap);
	return (n);
}
