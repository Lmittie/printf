/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_floats.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 19:14:04 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/23 20:42:46 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	if_not_minus_flag(t_arr *dec, t_arr *frac, t_printf *data, int i)
{
	char diff;

	diff = 0;
	if (!(data->flag & MINUS) && data->width > 0 && data->flag & ZERO &&
		(dec->buff[0] == '-' || dec->buff[0] == '+' || dec->buff[0] == ' '))
	{
		write(data->fd, &dec->buff[0], 1);
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
			write(data->fd, "1", 1);
			data->printed++;
		}
		write(data->fd, dec->buff + diff, dec->length - diff);
		write(data->fd, frac->buff, frac->length);
	}
	data->printed += dec->length;
	data->printed += frac->length;
}

void		print_float(t_arr *dec, t_arr *frac, t_printf *data, int i)
{
	int diff;

	diff = (data->precision - (int)frac->length > 0) ?
	data->precision - frac->length : 0;
	handle_overflow_buffer(data, diff +
	(data->width - (int)dec->length - (int)frac->length));
	if (frac->length == 1 && !(data->flag & SHARP))
		frac->length = 0;
	data->width = data->width - (int)dec->length - (int)frac->length - diff;
	if (data->width < 0)
		data->width = 0;
	if (data->flag & MINUS)
	{
		if (i)
		{
			write(data->fd, "1", 1);
			data->printed++;
		}
		write(data->fd, dec->buff, dec->length);
		write(data->fd, frac->buff, frac->length);
	}
	if_not_minus_flag(dec, frac, data, i);
	while (data->precision-- >= 0 && handle_overflow_buffer(data, 2))
		data->buff[data->length++] = '0';
	handle_overflow_buffer(data, 5000);
}
