/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_overflow_buffer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:32:58 by fmallist          #+#    #+#             */
/*   Updated: 2019/12/23 20:41:37 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		handle_overflow_buffer(t_printf *data, size_t len)
{
	if (data->length + len > 4096)
	{
		write(data->fd, data->buff, data->length);
		ft_bzero(data->buff, 4097);
		data->printed += data->length;
		data->length = 0;
	}
	return (1);
}
