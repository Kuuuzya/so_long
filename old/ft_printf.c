/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:30:36 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/25 13:52:05 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_printstring(char *s)
{
	int	count;

	count = 0;
	if (s == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	else
		count += ft_putstr(s);
	return (count);
}

int	ft_printnumber(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n > 9)
	{
		ft_printnumber(n / 10);
		ft_printnumber(n % 10);
	}
	else
		ft_putchar(n + '0');
	return (0);
}

static int	ft_parser(va_list params, const char *format, int i)
{
	int	count;

	count = 0;
	if (format[i] == 'd' || format[i] == 'i')
		count += ft_printnumber(va_arg(params, int));
	else if (format[i] == 's')
		count += ft_printstring(va_arg(params, char *));
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
