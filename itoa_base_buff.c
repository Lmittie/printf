/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base_buff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:26:07 by exam              #+#    #+#             */
/*   Updated: 2019/11/05 13:51:32 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char			neg_value(t_ll value, unsigned base, t_printf *data)
{
	char ch;

	if (value % (int)base <= -10)
	{
		if ((data->type & BIG_HEX) == BIG_HEX)
			ch = (value % (int)base) * -1 % 10 + 'A';
		else
			ch = (value % (int)base) * -1 % 10 + 'a';
	}
	else
		ch = (value % (int)base) * -1 + '0';
	return (ch);
}

static char			pos_value(t_ll value, unsigned base, t_printf *data)
{
	char ch;

	if (value % base >= 10)
	{
		if (data->type == BIG_HEX)
			ch = (value % base) % 10 + 'A';
		else
			ch = (value % base) % 10 + 'a';
	}
	else
		ch = (value % base) + '0';
	return (ch);
}

static char			result(t_ll value, unsigned base, t_printf *data)
{
	char ch;

	if (value < 0)
		ch = neg_value(value, base, data);
	else
		ch = pos_value(value, base, data);
	return (ch);
}

static t_ll			new_value(t_ll value, unsigned *base, t_ll *val)
{
	if (*base == BIG_HEX)
		*base = 16;
	if (*base == UNSIGNED)
		*base = 10;
	if (value < 0 && (*base == 8 || *base == 16))
		value = 0xFFFFFFFF + value + 1;
	*val = value;
	return (value);
}

int					check_flags(t_printf *data, t_ll value, unsigned base)
{
	if (value >= 0 && (data->flag & PLUS) && base == 10)
	{
		if (data->buff[data->length - 1] == '0' && (data->flag & ZERO))
			data->length--;
		data->buff[data->length++] = '+';
	}
	else if (value >= 0 && (data->flag & SPACE) && base == 10)
		data->buff[data->length++] = ' ';
	if ((((data->flag & SHARP) && base != 10)
			&& value != 0) || data->type & POINTER)
		data->buff[data->length++] = '0';
	if (((data->flag & SHARP) && (data->type == HEX)
			&& value) || data->type & POINTER)
		data->buff[data->length++] = 'x';
	else if ((data->flag & SHARP) && (data->type == BIG_HEX) && value)
		data->buff[data->length++] = 'X';
	if (data->flag & ZERO && data->flag & SHARP)
	{
		data->flag ^= SHARP;
		return (1);
	}
	return (0);
}

void				ya_ystala(int pos, t_printf *data, t_ll val)
{
	int i;

	i = 0;
	if (data->flag & ZERO && (val < 0 || data->flag & PLUS))
	{
		data->buff[pos] = '0';
		while (data->buff[pos - i] == '0')
			i++;
		if (val < 0)
			data->buff[pos - --i] = '-';
		else
			data->buff[pos - --i] = '+';
	}
}

void				itoa_base_buff(t_ll value, unsigned base, t_printf *data)
{
	size_t		len;
	t_ll		val;

	value = new_value(value, &base, &val);
	len = ft_numlen(value, base);
	if (check_flags(data, value, base))
		return ;
	while (value > base || value < -(int)base)
	{
		data->buff[data->length + (len--) - 1] = result(value, base, data);
		value = value / base;
	}
	if (value == base || value == -(int)base)
	{
		data->buff[data->length + len-- - 1] = '0';
		data->buff[data->length + len-- - 1] = '1';
	}
	else
		data->buff[data->length + len - 1] = result(value, base, data);
	if (data->flag & ZERO && (val < 0 || data->flag & PLUS) && base == 10)
		ya_ystala(data->length + (int)(len) - 2, data, val);
	else if (val < 0 && base == 10)
		data->buff[data->length + --len - 1] = '-';
	data->length += (ft_numlen(val, base));
}
