/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_integers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 21:03:31 by lmittie           #+#    #+#             */
/*   Updated: 2019/11/12 19:00:10 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		delete_zero_flag(t_printf *data, t_ll n)
{
	if (data->type & DECIMAL
	&& data->precision != 0 && data->flag & ZERO &&
	((data->precision > (t_ll)ft_numlen(n, 10)) || (data->width > (t_ll)ft_numlen(n, 10) && data->precision < (t_ll)ft_numlen(n, 10))))
		data->flag ^= ZERO;
	if (data->type & UNSIGNED && data->precision != 0 && data->flag & ZERO)
		data->flag ^= ZERO;
	if ((data->type == HEX || data->type == BIG_HEX) &&
	data->precision != 0 && data->flag & ZERO)
		data->flag ^= ZERO;
}

void			if_minus_flag2(t_printf *data, t_ll n)
{
	int prcn;
	int is_unsgn;
	int is_bhex;

	prcn = data->precision;
	is_bhex = (data->type == BIG_HEX) ? 1 : 0;
	is_unsgn = (data->type == UNSIGNED) ? 118 : 0;
	while (prcn-- > (t_ll)ft_numlen(n, data->type - is_bhex - is_unsgn)
						+ (data->type & OCTAL && data->flag & SHARP))
		data->buff[data->length++] = '0';
	if (data->type == UNSIGNED)
		itoa_base_buff_u(n, data);
	else
		itoa_base_buff(n, data->type, data);
}

void			if_minus_flag1(t_printf *data, t_ll n, t_ll *width, int *sharp)
{
	if (data->flag & MINUS && (!n && data->precision == -1)
	&& data->type & OCTAL && data->flag & SHARP)
		data->buff[data->length++] = '0';
	if (data->flag & MINUS && !n && data->precision == -1 && data->flag & PLUS)
			data->buff[data->length++] = '+';
	if ((data->flag & MINUS || (data->flag & ZERO && data->flag & SHARP)) &&
	!(!n && data->precision == -1))
	{
		if (data->flag & SHARP && (data->type == HEX || data->type == BIG_HEX)
		&& data->precision != 0 && n)
		{
			data->buff[data->length++] = '0';
			if (data->type == HEX)
				data->buff[data->length++] = 'x';
			else
				data->buff[data->length++] = 'X';
			data->flag ^= SHARP;
			*width -= 2;
			*sharp = 0;
		}
		if_minus_flag2(data, n);
	}
}

void			if_not_minus_flag2(t_printf *data, t_ll n)
{
	if (!(data->flag & MINUS) && (!n && data->precision == -1)
	&& data->flag & PLUS)
			data->buff[data->length++] = '+';
	if (!(data->flag & MINUS) && (!n && data->precision == -1)
	&& data->type & OCTAL && data->flag & SHARP)
		data->buff[data->length++] = '0';
}

void			if_not_minus_flag1(t_printf *data, t_ll n, int *sharp)
{
	int prcn;
	int is_bhex;
	int is_unsgn;

	prcn = data->precision;
	is_bhex = (data->type == BIG_HEX) ? 1 : 0;
	is_unsgn = (data->type == UNSIGNED) ? 118 : 0;
	if (!(data->flag & MINUS) && !(!n && data->precision == -1))
	{
		if (data->flag & SHARP && (data->type == HEX
		|| data->type == BIG_HEX) && data->precision != 0 && n)
		{
			data->buff[data->length++] = '0';
			if (data->type == HEX)
				data->buff[data->length++] = 'x';
			else
				data->buff[data->length++] = 'X';
			data->flag ^= SHARP;
			*sharp = 0;
		}
		while (prcn-- > (t_ll)ft_numlen(n, data->type
		- is_bhex - is_unsgn) + (data->type & OCTAL && *sharp))
			data->buff[data->length++] = '0';
		itoa_base_buff(n, data->type, data);
	}
	if_not_minus_flag2(data, n);
}

void			handle_integers(t_printf *data)
{
	t_ll	n;
	int		is_bhex;
	int		is_sharp;
	int		excpn;
	int		prcn;
	int		is_unsgn;
	t_ll	width;

	get_integer(data, &n);
	width = data->width;
	is_bhex = (data->type == BIG_HEX) ? 1 : 0;
	is_sharp = (data->flag & SHARP) ? 1 : 0;
	is_unsgn = (data->type == UNSIGNED) ? 118 : 0;
	excpn = (!n && data->precision == -1) ? 1 : 0;
	delete_zero_flag(data, n);
	handle_overflow_buffer(data, data->width +
	ft_numlen(n, data->type - is_bhex - is_unsgn) + (((data->flag & PLUS && n >= 0) ||
	(data->flag & SHARP && data->type & OCTAL)) ? 1 : 0) + ((data->type & HEX)
	|| (data->type & BIG_HEX) ? 2 : 0));
	if_minus_flag1(data, n, &width, &is_sharp);
	prcn = (data->precision < (t_ll)ft_numlen(n, data->type - is_bhex - is_unsgn)) ?
			(t_ll)ft_numlen(n, data->type - is_bhex - is_unsgn) : data->precision;
	if (data->type & DECIMAL && prcn == data->precision && n < 0
	&& data->precision > (t_ll)ft_numlen(n, 10))
		prcn++;
	if (!(data->flag & MINUS) && data->flag & SHARP && (data->type == HEX || data->type == BIG_HEX) && n
	&& data->precision > (t_ll)ft_numlen(n, data->type - is_bhex - is_unsgn))
		width -= 2;
	//printf("wid::%lld\n", width);
	//printf("prc::%lld\n", prcn);
	while (width-- - prcn -
	((((data->type == HEX) || (data->type == BIG_HEX)) && is_sharp && n
	&& data->precision < (t_ll)ft_numlen(n, data->type - is_bhex - is_unsgn)) ? 2 : 0)
	- (is_sharp && data->type & OCTAL && n && data->precision < (t_ll)ft_numlen(n, data->type - is_bhex - is_unsgn))
	+ (excpn && !(data->type & OCTAL && is_sharp))
	- ((data->type & DECIMAL && (data->flag & PLUS || data->flag & SPACE) && n >= 0) ? 1 : 0) > 0)
		data->buff[data->length++] = 32 + ((data->flag & ZERO) ? 16 : 0);
	if_not_minus_flag1(data, n, &is_sharp);
}