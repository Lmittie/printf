/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:15:28 by fmallist          #+#    #+#             */
/*   Updated: 2019/12/21 20:27:54 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				count_zeros(t_float *n)
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

int				handle_f_dec(t_arr *arr, char num, char flag)
{
	int len;

	len = arr->length;
	if (num - 48 > 5)
		add_one(arr, &flag, len);
	else if (num - 48 == 5)
		if ((arr->buff[len - 1] - 48) % 2 != 0)
			add_one(arr, &flag, len);
	while (len-- > 0 && flag)
		add_one(arr, &flag, len + 1);
	if (flag)
		return (1);
	return (0);
}

int				handle_f_prec(t_arr *arr, t_arr *dec, t_printf *data)
{
	size_t	len;
	char	flag;
	char	num;

	len = arr->length - 1;
	flag = 0;
	if (arr->buff[len] - '0' >= 5 && arr->buff[len - 1] != '.')
		add_one(arr, &flag, len);
	len--;
	while (arr->buff[len-- - 1] != '.' && flag)
		add_one(arr, &flag, len + 1);
	num = arr->buff[1];
	arr->buff[arr->length-- - 1] = '\0';
	if (flag || data->precision == 1)
		flag = handle_f_dec(dec, num, flag);
	return (flag);
}

void			init_float_bitfields(t_float *number, t_printf *data)
{
	int			i;
	int			j;
	__uint128_t	bits;

	i = 51;
	j = 0;
	bits = *(__uint128_t *)(&number->num);
	number->exp = ((bits >> 52) & 0x7FF) - 1023;
	if (number->exp >= 0 && (bits != 0 || !((bits >> 63) & 1)))
		number->decimal.arr[0] = 1;
	number->decimal.size_num = 1;
	number->sign = bits >> 63;
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
		number->num += number->num > 0 ? 1 : -1;
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
	i = number->fractional.size_num - 1;
	before_print_float(*number, data);
}

void			init_ldbl_bitfields(t_ldbl *number, t_printf *data)
{
	int			i;
	int			j;
	__uint128_t	bits;

	i = 62;
	j = 0;
	bits = *(__uint128_t *)(&number->num);
	number->exp = ((bits >> 64) & 0x7FFF) - 16383;
	if (number->exp >= 0 && (bits != 0 || !((bits >> 79) & 1)))
		number->decimal.arr[0] = 1;
	number->decimal.size_num = 1;
	number->sign = bits >> 79;
	if (number->exp > 0)
		while (i > 62 - number->exp)
		{
			multiply_long_short(&number->decimal, 2);
			if (((bits >> (__uint128_t)i) & 1) && i >= 0)
				add_long_short(&number->decimal, 1);
			i--;
		}
	if (number->exp < 0)
	{
		number->num += number->num > 0 ? 1 : -1;
		bits = *(__uint128_t *)(&(number->num));
		number->exp = ((bits >> 64) & 0x7FFF) - 16383;
	}
	i = 63 - number->exp;
	while (--i >= 0)
	{
		multiply_long_short(&number->fractional, 10);
		if ((bits >> i) & 1)
			add_long_long(&number->fractional,
			big_power_of_five(63 - number->exp - i));
	}
	before_print_ldbl(*number, data);
}

void			handle_floats(t_printf *data)
{
	t_float	fl;
	t_ldbl	ldbl;

	ft_bzero(&fl, sizeof(t_float));
	ft_bzero(&ldbl, sizeof(t_ldbl));
	if (data->size == BIGL)
	{
		ldbl.num = (long double)va_arg(data->ap, long double);
		data->type = FL;
		init_ldbl_bitfields(&ldbl, data);
	}
	else
	{
		fl.num = va_arg(data->ap, double);
		data->type = FL;
		init_float_bitfields(&fl, data);
	}
}
