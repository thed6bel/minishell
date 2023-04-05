/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:30:21 by lowathar          #+#    #+#             */
/*   Updated: 2023/02/21 14:00:32 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_x(t_struct *tab, va_list *ap)
{
	char			*str;
	unsigned int	nb;
	int				i;

	i = 0;
	nb = va_arg(*ap, unsigned int);
	if (tab->convert == 'x')
		str = ft_itoa_base(nb, "0123456789abcdef", 16);
	else
		str = ft_itoa_base(nb, "0123456789ABCDEF", 16);
	while (str[i] != '\0')
	{
		ft_putchar(str[i], tab);
		i++;
	}
	free (str);
	return (0);
}
