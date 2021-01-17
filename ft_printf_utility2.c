/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utility2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoki <saoki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:36:58 by saoki             #+#    #+#             */
/*   Updated: 2021/01/14 20:29:22 by saoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void					initialize_data(t_data_flag *data, int n)
{
	data->flag[FLAG_ZERO] = 0;
	data->flag[FLAG_MINUS] = 0;
	data->flag[FLAG_SHARP] = 0;
	data->field = 0;
	data->precision = -1;
	data->specifier = -1;
	data->sum_printed_len = n;
	data->printed_len = 0;
}

void					print_digit_re(unsigned long long n, char *base,
		unsigned int size)
{
	char				c;

	if (n >= size)
		print_digit_re(n / size, base, size);
	c = base[n % size];
	write(1, &c, sizeof(char));
}

void					putnbr_diux(unsigned long long num, t_data_flag data)
{
	if (data.specifier == SPEC_SX || data.specifier == SPEC_P)
		print_digit_re(num, "0123456789abcdef", 16);
	else if (data.specifier == SPEC_LX)
		print_digit_re(num, "0123456789ABCDEF", 16);
	else
		print_digit_re(num, "0123456789", 10);
}

int						get_digit_di(long long num)
{
	int					i;
	unsigned long long	n;

	i = 0;
	if (num < 0)
		n = -num;
	else
		n = num;
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

int						get_digit_ux(unsigned long long num, t_data_flag data)
{
	int					i;

	i = 0;
	while (num > 0)
	{
		i++;
		if (data.specifier == SPEC_U)
			num /= 10;
		else
			num /= 16;
	}
	return (i);
}
