/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_specifiers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 20:21:38 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/21 20:35:52 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			get_flags(t_printf *data, const char **format)
{
	while ((**format == '#' || **format == '-' || **format == '+'
							|| **format == ' ' || **format == '0'))
	{
		if (!(data->flag & SHARP) && **format == '#')
			data->flag |= SHARP;
		if (!(data->flag & ZERO) && **format == '0')
			data->flag |= ZERO;
		if (!(data->flag & PLUS) && **format == '+')
			data->flag |= PLUS;
		if (!(data->flag & MINUS) && **format == '-')
			data->flag |= MINUS;
		if (!(data->flag & SPACE) && **format == ' ')
			data->flag |= SPACE;
		*format += 1;
	}
	if (data->flag & ZERO && (data->flag & MINUS))
		data->flag ^= ZERO;
	if (data->flag & SPACE && data->flag & PLUS)
		data->flag ^= SPACE;
	get_width(data, format);
}

void			get_width(t_printf *data, const char **format)
{
	if (**format)
		data->width = ft_atoi(*format);
	if (**format == '*')
	{
		data->width = va_arg(data->ap, int);
		if (data->width < 0)
		{
			data->flag |= MINUS;
			data->width *= -1;
		}
		*format += 1;
	}
	if (**format && ft_isdigit(**format))
	{
		while (ft_isdigit(**format))
			*format += 1;
	}
}

void			get_precision(t_printf *data, const char **format)
{
	if (**format == '.')
	{
		*format += 1;
		if (**format == '*')
		{
			data->precision = va_arg(data->ap, int);
			*format += 1;
		}
		else
		{
			data->precision = ft_atoi(*format);
			if (**format == '0' && data->precision == 0)
				data->precision = -1;
			if (ft_isalpha(**format) && data->precision == 0)
				data->precision = -1;
			while (ft_isdigit(**format))
				*format += 1;
		}
	}
}

void			get_size(t_printf *data, const char **format)
{
	if (**format == 'h' && *(*format + 1) == 'h')
		data->size = HH;
	else if (**format == 'l' && *(*format + 1) == 'l')
		data->size = LL;
	else if (**format == 'h')
		data->size = H;
	else if (**format == 'l' || **format == 'z')
		data->size = L;
	else if (**format == 'L')
		data->size = BIGL;
	if (data->size & H || data->size & BIGL || data->size & L)
		*format += 1;
	else if ((data->size & HH) || (data->size & LL))
		*format += 2;
}
