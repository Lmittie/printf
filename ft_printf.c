/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:39:31 by fmallist          #+#    #+#             */
/*   Updated: 2019/11/02 20:50:33 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *format, ...)
{
	t_printf	data;
	int			bytes;

	ft_bzero(&data, sizeof(t_printf));
	va_start(data.ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			fill_options(&data, &format);
			continue ;
		}
		data.buff[data.length++] = *format++;
	}
	data.buff[data.length] = '\0';
	va_end(data.ap);
	bytes = write(1, data.buff, data.length);
	if (bytes == -1)
		return (0);
	return (bytes);
}
