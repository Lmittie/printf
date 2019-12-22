/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 21:03:31 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/21 20:26:32 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			delete_zero_flag(t_printf *data)
{
	if (data->precision != 0 && data->flag & ZERO)
		data->flag ^= ZERO;
}

static void			if_minus_flag(t_printf *data, t_ull n)
{
	int prcn;

	prcn = data->precision;
	if (data->flag & MINUS && !n && data->precision == -1 && data->flag & PLUS)
		data->buff[data->length++] = '+';
	while (prcn-- > (t_ll)ft_numlen_u(n))
		data->buff[data->length++] = '0';
	itoa_base_buff_u(n, data);
}

static void			if_not_minus_flag(t_printf *data, t_ull n)
{
	int prcn;

	prcn = data->precision;
	while (prcn-- > (t_ll)ft_numlen_u(n))
		data->buff[data->length++] = '0';
	itoa_base_buff_u(n, data);
	if (!(data->flag & MINUS) && (!n && data->precision == -1)
	&& data->flag & PLUS)
		data->buff[data->length++] = '+';
}

void				handle_unsigned(t_printf *data)
{
	t_ull	n;
	int		excpn;
	int		prcn;
	t_ll	width;
	t_ll	len;

	get_unsigned(data, &n);
	len = (t_ll)ft_numlen_u(n);
	width = data->width;
	excpn = (!n && data->precision == -1) ? 1 : 0;
	delete_zero_flag(data);
	handle_overflow_buffer(data, data->width +
	len + (data->flag & PLUS));
	if (data->flag & MINUS && !excpn)
		if_minus_flag(data, n);
	prcn = (int)((data->precision < len) ? len : data->precision);
	while (width-- - prcn + excpn > 0)
		data->buff[data->length++] = 32 + ((data->flag & ZERO) ? 16 : 0);
	if (!(data->flag & MINUS) && !excpn)
		if_not_minus_flag(data, n);
}
