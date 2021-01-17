/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoki <saoki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:54:35 by saoki             #+#    #+#             */
/*   Updated: 2021/01/17 09:35:55 by saoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void					print_int(va_list *ap, t_data_flag *data)
{
	long long			num;

	num = va_arg(*ap, int);
	get_putlen_di(data, num);
	if (!data->flag[FLAG_MINUS] && !data->flag[FLAG_ZERO])
		printf_putchar(' ', data->field);
	put_minus(num);
	if (!data->flag[FLAG_MINUS] && data->flag[FLAG_ZERO])
		printf_putchar('0', data->precision + data->field);
	else
		printf_putchar('0', data->precision);
	if (num < 0)
		num *= -1;
	if (num)
		putnbr_diux(num, *data);
	if (data->flag[FLAG_MINUS])
		printf_putchar(' ', data->field);
}

void					get_putlen_di(t_data_flag *data, long long num)
{
	if (data->flag[FLAG_ZERO] && (data->precision == -1))
		data->flag[FLAG_ZERO] = 1;
	else
		data->flag[FLAG_ZERO] = 0;
	data->printed_len = get_digit_di(num);
	if (data->precision <= data->printed_len)
		data->precision = (num == 0 && data->precision);
	else
		data->precision -= data->printed_len;
	if (num < 0)
		data->printed_len += data->precision + 1;
	else
		data->printed_len += data->precision;
	if (data->field <= data->printed_len)
		data->field = 0;
	else
		data->field -= data->printed_len;
}

void					print_unsigned(va_list *ap, t_data_flag *data)
{
	unsigned long long	num;

	num = va_arg(*ap, unsigned int);
	get_putlen_ux(data, num);
	if (!data->flag[FLAG_MINUS] && !data->flag[FLAG_ZERO])
		printf_putchar(' ', data->field);
	if (data->flag[FLAG_SHARP] && num != 0 && data->specifier != 2)
	{
		if (data->specifier == 3)
			write(1, "0x", 2);
		else
			write(1, "0X", 2);
	}
	if (!data->flag[FLAG_MINUS] && data->flag[FLAG_ZERO])
		printf_putchar('0', data->precision + data->field);
	else
		printf_putchar('0', data->precision);
	if (num)
		putnbr_diux(num, *data);
	if (data->flag[FLAG_MINUS])
		printf_putchar(' ', data->field);
}

void					get_putlen_ux(t_data_flag *data, unsigned long long num)
{
	if (data->flag[FLAG_ZERO] && (data->precision == -1))
		data->flag[FLAG_ZERO] = 1;
	else
		data->flag[FLAG_ZERO] = 0;
	data->printed_len = get_digit_ux(num, *data);
	if (data->precision <= data->printed_len)
		data->precision = (num == 0 && data->precision);
	else
		data->precision -= data->printed_len;
	if (data->flag[FLAG_SHARP] && num != 0 && data->specifier != SPEC_U)
		data->printed_len += data->precision + 2;
	else
		data->printed_len += data->precision;
	if (data->field <= data->printed_len)
		data->field = 0;
	else
		data->field -= data->printed_len;
}

