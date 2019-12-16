/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:54:57 by fmallist          #+#    #+#             */
/*   Updated: 2019/11/18 19:17:05 by fmallist         ###   ########.fr       */
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
			data->width = ABS(data->width);
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
		data->precision = ft_atoi(*format);
		if (**format == '0' && data->precision == 0)
			data->precision = -1;
		if (ft_isalpha(**format) && data->precision == 0)
			data->precision = -1;
		while (ft_isdigit(**format))
			*format += 1;
	}
	else if (**format == '*')
	{
		data->precision = va_arg(data->ap, int);
		*format += 1;
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
	else if (**format == 'l')
		data->size = L;
	else if (**format == 'L')
		data->size = BIGL;
	if (data->size & H || data->size & BIGL || data->size & L)
		*format += 1;
	else if ((data->size & HH) || (data->size & LL))
		*format += 2;
}

int			fill_options(t_printf *data, const char **format)
{
	get_flags(data, format);
	get_precision(data, format);
	get_size(data, format);
	if (**format == '%')
		data->type = PERCENT;
	else if (**format == 'c')
		data->type = CHAR;
	else if (**format == 's')
		data->type = STRING;
	else if (**format == 'p')
		data->type = POINTER;
	else if (**format == 'd' || **format == 'i')
		data->type = DECIMAL;
	else if (**format == 'o')
		data->type = OCTAL;
	else if (**format == 'x')
		data->type = HEX;
	else if (**format == 'X')
		data->type = BIG_HEX;
	else if (**format == 'u')
		data->type = UNSIGNED;
	else if (**format == 'f')
		data->type = FL;
	else
		return (0);
	push_buffer(data);
	*format += 1;
	return (1);
}
