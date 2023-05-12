/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:15:56 by lowathar          #+#    #+#             */
/*   Updated: 2023/02/21 14:00:19 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_p(t_struct *tab, va_list *ap)
{
	char				*str;
	unsigned long long	nb;
	int					i;

	i = 0;
	nb = va_arg(*ap, unsigned long long);
	str = ft_itoa_base(nb, "0123456789abcdef", 16);
	ft_putchar('0', tab);
	ft_putchar('x', tab);
	while (str[i] != '\0')
	{
		ft_putchar(str[i], tab);
		i++;
	}
	free (str);
	return (0);
}
