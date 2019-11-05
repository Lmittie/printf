/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_overflow_buffer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:32:58 by fmallist          #+#    #+#             */
/*   Updated: 2019/10/31 15:33:13 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		handle_overflow_buffer(t_printf *data, size_t len)
{
	if (data->length + len > 4096)
	{
		write(1, data->buff, data->length);
		ft_bzero(data->buff, 4097);
		data->printed += data->length;
		data->length = 0;
	}
	return (1);
}
