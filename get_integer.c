/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_integer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:14:42 by fmallist          #+#    #+#             */
/*   Updated: 2019/11/05 14:12:13 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_integer(t_printf *data, long long *n)
{
	*n = va_arg(data->ap, long long);
	if (data->type & UNSIGNED)
	{
		if (data->size & H)
			*n = (unsigned short)*n;
		else if (data->size & HH)
			*n = (unsigned char)*n;
		else if (!(data->size & L) && !(data->size & LL))
			*n = (unsigned int)*n;
		if (data->flag & PLUS)
			data->flag ^= PLUS;
		else if (data->flag & SPACE)
			data->flag ^= SPACE;
	}
	else
	{
		if (data->size & H)
			*n = (short)*n;
		else if (data->size & HH)
			*n = (char)*n;
		else if (!(data->size & L) && !(data->size & LL))
			*n = (int)*n;
	}
}
