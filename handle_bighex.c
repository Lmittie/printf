/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bighex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:32:02 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/21 20:33:19 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			if_minus_flag(t_printf *data, t_ll n,
t_ll *width, int *sharp)
{
	int prcn;

	prcn = data->precision;
	if (data->flag & MINUS && !n && data->precision == -1 && data->flag & PLUS)
		data->buff[data->length++] = '+';
	if ((data->flag & MINUS || (data->flag & ZERO && data->flag & SHARP)) &&
	!(!n && data->precision == -1))
	{
		if (data->flag & SHARP && data->precision != 0 && n)
		{
			data->buff[data->length++] = '0';
			data->buff[data->length++] = 'X';
			data->flag ^= SHARP;
			*width -= 2;
			*sharp = 0;
		}
		while (prcn-- > (t_ll)ft_numlen(n, data->type - 1))
			data->buff[data->length++] = '0';
		itoa_base_buff(n, data->type, data);
	}
}

static void			if_not_minus_flag(t_printf *data, t_ll n, int *sharp)
{
	int prcn;

	prcn = data->precision;
	if (!(data->flag & MINUS) && !(!n && data->precision == -1))
	{
		if (data->flag & SHARP && data->precision != 0 && n)
		{
			data->buff[data->length++] = '0';
			data->buff[data->length++] = 'X';
			data->flag ^= SHARP;
			*sharp = 0;
		}
		while (prcn-- > (t_ll)ft_numlen(n, data->type - 1))
			data->buff[data->length++] = '0';
		itoa_base_buff(n, data->type, data);
	}
	if (!(data->flag & MINUS) && (!n && data->precision == -1)
	&& data->flag & PLUS)
		data->buff[data->length++] = '+';
}

void				handle_bighex(t_printf *data)
{
	t_ll	n;
	int		is_sharp;
	int		prcn;
	t_ll	width;
	t_ll	len;

	get_integer(data, &n);
	len = (t_ll)ft_numlen(n, 16);
	width = data->width;
	is_sharp = (data->flag & SHARP) ? 1 : 0;
	if (data->precision != 0 && data->flag & ZERO)
		data->flag ^= ZERO;
	// handle_overflow_buffer(data, data->width +
	// ft_numlen(n, data->type - is_bhex - is_unsgn) + (((data->flag & PLUS && n >= 0) ||
	// (data->flag & SHARP && data->type & OCTAL)) ? 1 : 0) + ((data->type & HEX)
	// || (data->type & BIG_HEX) ? 2 : 0));
	if_minus_flag(data, n, &width, &is_sharp);
	prcn = (data->precision < len) ? len : data->precision;
	if (!(data->flag & MINUS) && data->flag & SHARP
	&& n && data->precision > len)
		width -= 2;
	while (width-- - prcn -
	((is_sharp && n && data->precision < len) ? 2 : 0)
	+ ((!n && data->precision == -1) && !(data->type & OCTAL && is_sharp)) > 0)
		data->buff[data->length++] = 32 + ((data->flag & ZERO) ? 16 : 0);
	if_not_minus_flag(data, n, &is_sharp);
}
