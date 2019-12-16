/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:15:28 by fmallist          #+#    #+#             */
/*   Updated: 2019/11/26 20:58:2 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <float.h>

int			count_zeros(t_float *n)
{
	unsigned last;
	if (n->fractional.size_num == 0)
		return (0);
	last = ft_numlen_u(n->fractional.arr[n->fractional.size_num - 1]);
	return (52 - n->exp - 9 * (n->fractional.size_num - 1) - last);
}

static void		add_one(t_arr *arr, char *flag, size_t len)
{
	*flag = 0;
	if (arr->buff[len - 1] == '9')
	{
		arr->buff[len - 1] = '0';
		*flag = 1;
	}
	else
		arr->buff[len - 1] += 1;
}

static void		handle_f_prec(t_arr *arr, t_printf *data)
{
	size_t	len;
	char	flag;

	len = arr->length - 1;
	flag = 0;
	if (arr->buff[len] - 48 > 5)
		add_one(arr, &flag, len);
	else if (arr->buff[len] - 48 == 5)
		if ((arr->buff[len - 1] - 48) % 2 != 0)
			add_one(arr, &flag, len);
	len--;
	while (arr->buff[len - 1] != '.' && flag)
	{
		add_one(arr, &flag, len);
		len--;
	}
	arr->buff[arr->length-- - 1] = '\0';
}

static void		print_float(t_float number, t_printf *data)
{
	unsigned zeros;
	int i, j;
	int prec;
	unsigned int base;
	t_arr dec;
	t_arr frac;

	j = 0;
	i = 0;
	i = number.decimal.size_num - 1;
	ft_bzero(&dec, sizeof(t_arr));
	//dec.length++;
	ft_bzero(&frac, sizeof(t_arr));
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
	printf("dec: %s\n", dec.buff);
	i = number.fractional.size_num - 1;
	base = 1;
	j = ft_numlen_u(number.fractional.arr[i]);
	while (--j)
		base = base * 10;
	zeros = count_zeros(&number);
	while (zeros--)
		frac.buff[frac.length++] = '0';
	if (data->precision == 0)
		data->precision = 6;
	if (data->precision == -1)
		data->precision = 0;
	data->precision++;
	prec = data->precision;
	zeros = count_zeros(&number);
	while (zeros >= 9)
	{
		zeros -= 9;
		prec -= 9;
		i--;
	}
	prec -= zeros;
	if (i >= 0 && prec > 0)
	{
		while (i >= 0 && prec > 0)
		{
			j = 9 - ft_numlen_u(number.fractional.arr[i]);
			if ((unsigned)i == number.fractional.size_num - 1)
				j = 0;
			while (j-- > 0)
				frac.buff[frac.length++] = '0';
			if (((unsigned)i != number.fractional.size_num - 1 &&  prec < 9) ||
	(prec < ft_numlen_u(number.fractional.arr[i]) && (unsigned)i == number.fractional.size_num - 1))
				while (prec--)
				{
					if (base != 0 && (number.fractional.arr[i] / base) % 10 == 0)
						frac.buff[(frac.length)++] = '0';
					else if (base != 0)
						frac.buff[(frac.length)++] = (number.fractional.arr[i] / base) % 10 + '0';
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
		while (prec-- >= 0)
			frac.buff[frac.length++] = '0';
		handle_f_prec(&frac, data);
	}
	else
		while (prec-- - 1 > 0)
			frac.buff[frac.length++] = '0';
	printf("frac: %s\n", frac.buff);
}

void		init_float_bitfields(t_float *number, t_printf *data)
{
	int			i;
	int			j;
	__uint128_t	bits;

	i = 51;
	j = 0;
	number->fractional.arr[0] = 1;
	bits = *(__uint128_t *)(&number->num);
	number->exp = ((bits >> 52) & 0x7FF) - 1023;
	if (number->exp >= 0 && (bits != 0 || !((bits >> 63) & 1)))
		number->decimal.arr[0] = 1;
	number->decimal.size_num = 1;
	if (number->exp > 0)
		while (i > 51 - number->exp)
		{
			multiply_long_short(&number->decimal, 2);
			if (((bits >> (__uint128_t)i) & 1) && i >= 0)
				add_long_short(&number->decimal, 1);
			i--;
		}
	if (number->exp < 0)
	{
		number->num++;
		bits = *(__uint128_t *)(&(number->num));
		number->exp = ((bits >> 52) & 0x7FF) - 1023;
	}
	i = 52 - number->exp;
	while (--i >= 0)
	{
		multiply_long_short(&number->fractional, 10);
		if ((bits >> i) & 1)
			add_long_long(&number->fractional,
			big_power_of_five(52 - number->exp - i));
	}
	print_float(*number, data);
}

void		float_to_str(t_float *n, t_printf *data)
{
	data->type = FL;

	init_float_bitfields(n, data);
}

void		handle_floats(t_printf *data)
{
	t_float	fl;
	t_ldbl	ldbl;

	ft_bzero(&fl, sizeof(t_float));
	ft_bzero(&ldbl, sizeof(t_ldbl));


	if (data->size == BIGL)
	{
		ldbl.num = va_arg(data->ap, long double);
		//ldbl_to_str(&ldbl, data);
	}
	else
	{
		fl.num = va_arg(data->ap, double);
		float_to_str(&fl, data);
	}
}
