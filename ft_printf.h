/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:00:04 by fmallist          #+#    #+#             */
/*   Updated: 2019/11/13 15:47:00 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>

# define ABS(x) (x < 0) ? -x : x

/*-----------FLAGS---------------*/

# define MINUS				(1 << 0)
# define PLUS				(1 << 1)
# define ZERO				(1 << 2)
# define SPACE				(1 << 3)
# define SHARP				(1 << 4)

/*----------SIZE------------------*/

# define H					(1 << 1)
# define HH					(1 << 2)
# define L					(1 << 3)
# define LL					(1 << 4)
# define D					(1 << 5)
# define BIGL				(1 << 6)

/*---------TYPE--------------------*/

# define CHAR				(1 << 9)
# define STRING				(1 << 2)
# define POINTER			(1 << 5)
# define PERCENT			(1 << 6)
# define DECIMAL			10
# define OCTAL				8
# define UNSIGNED			(1 << 7)
# define HEX				16
# define BIG_HEX			17

# define MAX_LENGTH			4096

typedef long long			t_ll;
typedef unsigned long long	t_ull;

typedef struct	s_printf
{
	uint8_t		flag;
	t_ll		width;
	int			precision;
	uint16_t	size;
	uint32_t	type;
	size_t		length;
	char		buff[MAX_LENGTH + 1];
	va_list		ap;
	unsigned	printed;
}				t_printf;

void			get_width(t_printf *data, const char **format);
void			get_precision(t_printf *data, const char **format);
void			get_flags(t_printf *data, const char **format);
void			get_size(t_printf *data, const char **format);

int				ft_printf(const char *format, ...);
void			push_buffer(t_printf *data);
int				fill_options(t_printf *data, const char **format);
int				handle_overflow_buffer(t_printf *data, size_t len);
void			get_integer(t_printf *data, long long *n);
void			handle_integers(t_printf *data);

void			itoa_base_buff(t_ll value, unsigned base, t_printf *data);
char			neg_value(t_ll value, unsigned base, t_printf *data);
char			pos_value(t_ll value, unsigned base, t_printf *data);
char			result(t_ll value, unsigned base, t_printf *data);
t_ll			new_value(t_ll value, unsigned *base, t_ll *val, t_printf *data);

void			itoa_base_buff_u(t_ull value, t_printf *data);
void			get_unsigned(t_printf *data, t_ull *n);
size_t			ft_numlen_u(t_ull val);
void			handle_unsigned(t_printf *data);

#endif
