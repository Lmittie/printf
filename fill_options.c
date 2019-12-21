/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:54:57 by fmallist          #+#    #+#             */
/*   Updated: 2019/12/21 20:23:17 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		more_filling(t_printf *data, const char **format)
{
	if (**format == 'o')
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
	return (1);
}

int				fill_options(t_printf *data, const char **format)
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
	else if (!more_filling(data, format))
		return (0);
	push_buffer(data);
	*format += 1;
	return (1);
}
