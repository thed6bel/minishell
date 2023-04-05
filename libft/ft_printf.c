/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:39:10 by lowathar          #+#    #+#             */
/*   Updated: 2023/02/21 14:00:40 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, t_struct *tab)
{
	write(1, &c, 1);
	tab->count_print++;
}

int	ft_print_with_convert(t_struct *tab, va_list *ap)
{
	if (tab->convert == 'c')
		ft_print_c(tab, ap);
	else if (tab->convert == 's')
		return (ft_print_s(tab, ap));
	else if (tab->convert == 'p')
		return (ft_print_p(tab, ap));
	else if (tab->convert == 'd' || tab->convert == 'i')
		return (ft_print_i(tab, ap));
	else if (tab->convert == 'u')
		return (ft_print_u(tab, ap));
	else if (tab->convert == 'x' || tab->convert == 'X')
		return (ft_print_x(tab, ap));
	else if (tab->convert == '%')
		ft_putchar('%', tab);
	return (0);
}

int	ft_get_convert(t_struct *tab, const char *str, int i)
{
	if (str[i] == 'c' || str[i] == 's' || str[i] == 'p' || str[i] == 'd'
		|| str[i] == 'i' || str[i] == 'u' || str[i] == 'x'
		|| str[i] == 'X' || str[i] == '%')
	{
		tab->convert = str[i];
		return (i);
	}
	else
		return (-1);
}

int	ft_print(const char *format, va_list *ap, t_struct *tab)
{
	int	i;
	int	j;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			j = ft_get_convert(tab, format, i);
			if (j != -1)
			{
				if (ft_print_with_convert(tab, ap) == -1)
					return (-1);
			}
			else
				ft_putchar(format[i], tab);
		}
		else
			ft_putchar(format[i], tab);
		i++;
	}
	return (tab->count_print);
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	t_struct	tab;
	int			count;
	char		*f;

	tab.count_print = 0;
	f = (char *)format;
	va_start(ap, format);
	count = ft_print(f, &ap, &tab);
	if (count == -1)
		return (-1);
	va_end(ap);
	return (count);
}
