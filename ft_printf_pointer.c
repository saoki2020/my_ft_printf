#include "ft_printf.h"

void					print_pointer(va_list *ap, t_data_flag *data)
{
	unsigned long		num;

	data->specifier = SPEC_SX;
	data->flag[FLAG_SHARP] = 1;
	if ((num = (unsigned long)va_arg(*ap, void *)) == 0)
		pointer_null_nofit(data);
	else
		get_putlen_ux(data, num);
	if (!data->flag[FLAG_MINUS] && !data->flag[FLAG_ZERO])
		printf_putchar(' ', data->field);
	write(1, "0x", 2);
	if (!data->flag[FLAG_MINUS] && data->flag[FLAG_ZERO])
		printf_putchar('0', data->precision + data->field);
	else
		printf_putchar('0', data->precision);
	if (num)
		putnbr_diux(num, *data);
	if (data->flag[FLAG_MINUS])
		printf_putchar(' ', data->field);
}

void					pointer_null_nofit(t_data_flag *data)
{
			if (data->precision == -1)
			data->precision = 1;
		data->printed_len = 2 + data->precision;
		if (data->field <= data->precision)
			data->field = 0;
		else
				data->field -= (2 + data->precision);
		if (data->field < 0)
				data->field = 0;
}
