/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:39:31 by fmallist          #+#    #+#             */
/*   Updated: 2019/11/13 15:49:38 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			init_fields(t_printf *data)
{
	data->precision = 0;
	data->width = 0;
	data->type = 0;
	data->flag = 0;
	data->size = 0;
}

int				ft_printf(const char *format, ...)
{
	t_printf	data;

	ft_bzero(&data, sizeof(t_printf));
	va_start(data.ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			init_fields(&data);
			if (fill_options(&data, &format) == 0)
				return (write(1, data.buff, data.length));
			continue ;
		}
		data.buff[data.length++] = *format++;
	}
	data.buff[data.length] = '\0';
	va_end(data.ap);
	return (write(1, data.buff, data.length));
}
