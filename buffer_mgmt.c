/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:30:35 by fmallist          #+#    #+#             */
/*   Updated: 2019/12/21 19:30:15 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		while (--data->width > 0 && handle_overflow_buffer(data, 1))
			data->buff[data->length++] = 32 + ((data->flag & ZERO) ? 16 : 0);
		if (!(data->flag & MINUS))
			data->buff[data->length++] = '%';
	}
	else if (data->type == DECIMAL)
		handle_integers(data);
	else if (data->type == OCTAL)
		handle_octals(data);
	else if (data->type == HEX)
		handle_hexdecimals(data);
	else if (data->type == BIG_HEX)
		handle_bighex(data);
	else if (data->type == UNSIGNED)
		handle_unsigned(data);
	else if (data->type == FL)
		handle_floats(data);
}
