/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:03:41 by hucorrei          #+#    #+#             */
/*   Updated: 2023/02/01 14:06:55 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_format(va_list args, char format)
{
	int	print_len;

	print_len = 0;
	if (format == 'c')
		print_len += ft_printchar(va_arg(args, int));
	else if (format == 's')
		print_len += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		print_len += ft_printptr(va_arg(args, unsigned long));
	else if (format == 'd' || format == 'i')
		print_len += ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		print_len += ft_printunsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_len += ft_printhex(va_arg(args, unsigned int), format);
	else if (format == '%')
		print_len += ft_printpercent();
	else
		print_len += ft_printchar(format);
	return (print_len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		print_len;

	i = 0;
	print_len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			print_len += ft_format(args, str[i + 1]);
			i++;
		}
		else
			print_len += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (print_len);
}
