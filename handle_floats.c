
#include "ft_printf.h"

void			init_float_bitfields(t_float *number, t_printf *data)
{
	int			i;
	__uint128_t	bits;

	i = 51;
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
	__uint128_t	bits;

	i = 62;
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
