/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:30:36 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/21 16:34:03 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void ft_putchar(char c)
{
	write(1, &c, 1);
}

static void ft_putstr(char *s)
{
	if (s == NULL)
		return ;
	while (*s)
		write(1, s++, 1);
}

static int		ft_printstring(char *s)
{
	int		count;

	count = 0;
	if (s == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	else
		count += ft_putstr(s);
	return (ft_strlen(s));
}

static int	ft_parser(va_list params, const char *format, int i)
{
	int	count;

	count = 0;
	if (format[i] == 'c')
		count += ft_putchar(va_arg(params, int));
	else
		count += ft_putchar(format[i]);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	params;

	i = 0;
	count = 0;
	va_start(params, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_parser(params, format, i);
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(params);
	return (count);
}
