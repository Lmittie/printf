

#include "ft_printf.h"

void			handle_pointers(t_printf *data)
{
	t_ll n;

	n = (long)va_arg(data->ap, void *);
	handle_overflow_buffer(data, ft_numlen(n, 16) + data->width);
	if (data->flag & MINUS)
		itoa_base_buff(n, 16, data);
	while (data->width-- - (long long)ft_numlen(n, 16) - 2 > 0)
		data->buff[data->length++] = 32;
	if (!(data->flag & MINUS))
		itoa_base_buff(n, 16, data);
}

static void		string_spaces(t_printf *data, char *str)
{
	t_ll	what_bigger;
	int		pr_or_wid;

	what_bigger = ((t_ll)data->precision < (t_ll)ft_strlen(str)
	&& data->precision != 0 && data->precision != -1)
	? data->precision : (t_ll)ft_strlen(str);
	pr_or_wid = (data->precision > data->width) ? data->precision : 0;
	while ((data->width-- - ((*str == '\0' && (data->precision != 0
	|| data->precision != -1)) ? 0 : what_bigger + pr_or_wid)) > 0)
		data->buff[data->length++] = 32;
}

void			handle_strings(t_printf *data)
{
	char	*str;

	if ((str = (char *)va_arg(data->ap, char*)) == NULL)
		str = "(null)";
	if (data->precision == -1)
		str = "";
	if (data->flag & MINUS && *str != '\0' && data->precision != -1)
	{
		if (!data->precision || (t_ll)ft_strlen(str) < (t_ll)data->precision)
			ft_strcpy(&data->buff[data->length], str);
		else
			str = ft_strncpy(&data->buff[data->length], str, data->precision);
		data->length += ft_strlen(str);
	}
	string_spaces(data, str);
	if (!(data->flag & MINUS) && *str != '\0' && data->precision != -1)
	{
		if (!data->precision || (t_ll)ft_strlen(str) < (t_ll)data->precision)
			ft_strcpy(&data->buff[data->length], str);
		else
			str = ft_strncpy(&data->buff[data->length], str, data->precision);
		data->length += ft_strlen(str);
	}
}

void			handle_chars(t_printf *data)
{
	handle_overflow_buffer(data, data->width + 1);
	if (data->flag & MINUS)
		data->buff[data->length++] = (char)va_arg(data->ap, int);
	while (--data->width > 0)
		data->buff[data->length++] = 32;
	if (!(data->flag & MINUS))
		data->buff[data->length++] = (char)va_arg(data->ap, int);
}

