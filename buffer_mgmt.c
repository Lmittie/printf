/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:30:35 by fmallist          #+#    #+#             */
/*   Updated: 2019/11/05 13:59:11 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void			handle_pointers(t_printf *data)
{
	t_ll n;

	n = (long)va_arg(data->ap, void *);
	handle_overflow_buffer(data, ft_numlen(n, 16) + data->width);
	if (data->flag & MINUS)
		itoa_base_buff(n, 16, data);
	while (data->width-- - (long long)ft_numlen(n, 16) - 2 > 0)
		data->buff[data->length++] = 32;
	if (!(data->flag & MINUS))
		itoa_base_buff(n, 16, data);
}

void			handle_strings(t_printf *data)
{
	char *str;

	if ((str = (char *)va_arg(data->ap, char*)) == NULL)
	{
		if (data->flag & MINUS)
		{
			if (!data->precision)
				ft_strcpy(&data->buff[data->length], "(null)");
			else
				ft_strncpy(&data->buff[data->length], "(null)", data->precision);
			data->length += 6 - data->precision;
		}
		while (data->width-- - data->precision > 0)
			data->buff[data->length++] = 32;
		if (!(data->flag & MINUS))
		{
			if (!data->precision)
				ft_strcpy(&data->buff[data->length], "(null)");
			else
				ft_strncpy(&data->buff[data->length], "(null)", data->precision);
			data->length += 6 - data->precision;
		}
		return ;
	}
	if (data->flag & MINUS && *str != '\0')
	{
		if (!data->precision)
			ft_strcpy(&data->buff[data->length], str);
		else
			ft_strncpy(&data->buff[data->length], str, data->precision);
		data->length += ft_strlen(str) - data->precision;
	}
	while (data->width-- - (long long)ft_strlen(str) + ((*str != '\0') ?
												data->precision : 0) > 0)
		data->buff[data->length++] = 32;
	if (!(data->flag & MINUS) && *str != '\0')
	{
		if (!data->precision)
			ft_strcpy(&data->buff[data->length], str);
		else
			ft_strncpy(&data->buff[data->length], str, data->precision);
		data->length += ft_strlen(str) - data->precision;
	}
}

void			handle_chars(t_printf *data)
{
	handle_overflow_buffer(data, data->width + 1);
	if (data->flag & MINUS)
		data->buff[data->length++] = (char)va_arg(data->ap, int);
	while (--data->width > 0)
		data->buff[data->length++] = 32;
	if (!(data->flag & MINUS))
		data->buff[data->length++] = (char)va_arg(data->ap, int);
}

void			handle_integers(t_printf *data)
{
	t_ll	n;
	int		is_bhex;
	int		is_sharp;
	int		is_fignya;
	int		prcn;
	int		is_unsgn;

	get_integer(data, &n);
	prcn = data->precision;
	is_bhex = (data->type == BIG_HEX) ? 1 : 0;
	is_unsgn = (data->type == UNSIGNED) ? 5 : 0;
	is_sharp = (data->flag & SHARP) ? 1 : 0;
	is_fignya = (!n && data->precision == -1) ? 1 : 0;
	handle_overflow_buffer(data, data->width +
	ft_numlen(n, data->type - is_bhex) + (((data->flag & PLUS && n >= 0) ||
	(data->flag & SHARP && data->type & OCTAL)) ? 1 : 0) + ((data->type & HEX)
	|| (data->type & BIG_HEX) ? 2 : 0));
	if (is_fignya && data->type & OCTAL && data->flag & SHARP)
		data->buff[data->length++] = '0';
	if ((data->flag & MINUS || (data->flag & ZERO && data->flag & SHARP)) && !is_fignya)
	{
		while (prcn-- > (t_ll)ft_numlen(n, data->type - is_bhex - is_unsgn))
			data->buff[data->length++] = '0';
		itoa_base_buff(n, data->type, data);
	}
	prcn = (data->precision < (t_ll)ft_numlen(n, data->type - is_bhex - is_unsgn)) ?
			(t_ll)ft_numlen(n, data->type - is_bhex - is_unsgn) : data->precision;
	while ((data->width--) - prcn -
	((((data->type == HEX) || (data->type == BIG_HEX)) && is_sharp) ? 2 : 0)
	- ((is_sharp && data->type & OCTAL) ? 1 : 0) + is_fignya - is_bhex - is_unsgn > 0)
		data->buff[data->length++] = 32 + ((data->flag & ZERO) ? 16 : 0);
	if (!(data->flag & MINUS) && !is_fignya)
	{
		while (prcn-- > (t_ll)ft_numlen(n, data->type - is_bhex))
			data->buff[data->length++] = '0';
		itoa_base_buff(n, data->type, data);
	}
}

void			push_buffer(t_printf *data)
{
	if (data->type & CHAR)
		handle_chars(data);
	else if (data->type & STRING)
		handle_strings(data);
	else if (data->type & POINTER)
		handle_pointers(data);
	else if (data->type & PERCENT &&
			handle_overflow_buffer(data, data->width + 1))
	{
		if (data->flag & MINUS)
			data->buff[data->length++] = '%';
		while (--data->width > 0)
			data->buff[data->length++] = 32;
		if (!(data->flag & MINUS))
			data->buff[data->length++] = '%';
	}
	else if (data->type & DECIMAL || data->type & OCTAL
	|| data->type == HEX || data->type == BIG_HEX || data->type & UNSIGNED)
		handle_integers(data);
}
