/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_ldbls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 20:50:56 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/20 21:24:17 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_zeros_ldbl(t_ldbl *n)
{
	unsigned last;
	if (n->fractional.size_num == 0)
		return (0);
	last = ft_numlen_u(n->fractional.arr[n->fractional.size_num - 1]);
	return (63 - n->exp - 9 * (n->fractional.size_num - 1) - last);
}

void		before_print_ldbl(t_ldbl number, t_printf *data)
{
	unsigned		zeros;
	int				i;
	int				j;
	int				prec;
	unsigned int	base;

	j = 0;
	i = 0;
	i = number.decimal.size_num - 1;
	VAR(t_arr, dec);
	VAR(t_arr, frac);
	ft_bzero(&dec, sizeof(t_arr));
	ft_bzero(&frac, sizeof(t_arr));
	if (number.sign)
		dec.buff[dec.length++] = '-';
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
	zeros = count_zeros_ldbl(&number);
	while (zeros--)
		frac.buff[frac.length++] = '0';
	if (data->precision == 0)
		data->precision = 6;
	if (data->precision == -1)
		data->precision = 0;
	data->precision++;
	prec = data->precision;
	zeros = count_zeros_ldbl(&number);
	while (zeros >= 9)
	{
		zeros -= 9;
		prec -= 9;
		i--;
	}
	prec -= zeros;
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
