/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_floats.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 19:14:04 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/21 15:40:55 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_float(t_arr *dec, t_arr *frac, t_printf *data, int i)
{
	int diff;

	diff = (data->precision - (int)frac->length > 0) ? data->precision - frac->length : 0;
	handle_overflow_buffer(data, diff + (data->width - (int)dec->length - (int)frac->length));
	if (frac->length == 1 && !(data->flag & SHARP))
		frac->length = 0;
	data->width = data->width - (int)dec->length - (int)frac->length - diff;
	if (data->width < 0)
		data->width = 0;
	if (data->flag & MINUS)
	{
		if (i)
		{
			write(1, "1", 1);
			data->printed++;
		}
		write(1, dec->buff, dec->length);
		write(1, frac->buff, frac->length);
	}
	diff = 0;
	if (!(data->flag & MINUS) && data->width > 0 && data->flag & ZERO &&
		(dec->buff[0] == '-' || dec->buff[0] == '+' || dec->buff[0] == ' '))
	{
		write(1, &dec->buff[0], 1);
		diff = 1;
		data->printed++;
	}
	while (data->width-- > 0 && handle_overflow_buffer(data, 2))
		data->buff[data->length++] = 32 + ((data->flag & ZERO) ? 16 : 0);
	handle_overflow_buffer(data, 5000);
	if (!(data->flag & MINUS))
	{
		if (i)
		{
			write(1, "1", 1);
			data->printed++;
		}
		write(1, dec->buff + diff, dec->length - diff);
		write(1, frac->buff, frac->length);
	}
	data->printed += dec->length;
	data->printed += frac->length;
	while (data->precision-- >= 0 && handle_overflow_buffer(data, 2))
		data->buff[data->length++] = '0';
	handle_overflow_buffer(data, 5000);
}

void		before_print_float(t_float number, t_printf *data)
{
	unsigned		zeros;
	int				i;
	int				j;
	int				prec;
	unsigned int	base;
	t_arr			dec;
	t_arr			frac;

	j = 0;
	i = 0;
	i = number.decimal.size_num - 1;
	ft_bzero(&dec, sizeof(t_arr));
	ft_bzero(&frac, sizeof(t_arr));
	if (number.sign)
		dec.buff[dec.length++] = '-';
	if (data->flag & PLUS && !number.sign)
		dec.buff[dec.length++] = '+';
	if (data->flag & SPACE && !number.sign)
		dec.buff[dec.length++] = ' ';
	while (i >= 0)
	{
		j = 9 - ft_numlen_u(number.decimal.arr[i]);
		if ((unsigned)i == number.decimal.size_num - 1)
			j = 0;
		while (j-- > 0)
			dec.buff[dec.length++] = '0';
		ftoa_base_buff(number.decimal.arr[i], &dec);
		i--;
	}
	frac.buff[frac.length++] = '.';
	i = number.fractional.size_num - 1;
	base = 1;
	j = ft_numlen_u(number.fractional.arr[i]);
	while (--j)
		base = base * 10;
	if (data->precision == 0)
		data->precision = 6;
	if (data->precision == -1)
		data->precision = 0;
	data->precision++;
	prec = data->precision;
	zeros = count_zeros(&number);
	while (zeros-- && prec--)
		frac.buff[frac.length++] = '0';
	if (prec <= 0)
		i = handle_f_prec(&frac, &dec, data);
	if (i >= 0 && prec > 0)
	{
		while (i >= 0 && prec > 0)
		{
			j = 9 - ft_numlen_u(number.fractional.arr[i]);
			if ((unsigned)i == number.fractional.size_num - 1)
				j = 0;
			while (j-- > 0 && prec >= 9)
				frac.buff[frac.length++] = '0';
			if (((unsigned)i != number.fractional.size_num - 1 && prec < 9) ||
	(prec < (int)ft_numlen_u(number.fractional.arr[i]) && (unsigned)i == number.fractional.size_num - 1))
				while (prec-- > 0)
				{
					if (base != 0 && (number.fractional.arr[i] / base) % 10 == 0)
						frac.buff[frac.length++] = '0';
					else if (base != 0)
						frac.buff[frac.length++] = (number.fractional.arr[i] / base) % 10 + '0';
					base /= 10;
				}
			else
				ftoa_base_buff(number.fractional.arr[i], &frac);
			if ((unsigned)i == number.fractional.size_num - 1)
				prec -= ft_numlen_u(number.fractional.arr[i]);
			else
				prec -= 9;
			base = 100000000;
			i--;
		}
		if (prec-- > 0)
			frac.buff[frac.length++] = '0';
		i = handle_f_prec(&frac, &dec, data);
	}
	else
	{
		while (prec-- - 1 > 0)
			frac.buff[frac.length++] = '0';
		i = 0;
	}
	data->precision = --prec;
	print_float(&dec, &frac, data, i);
}
