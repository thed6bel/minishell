/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:13:32 by lowathar          #+#    #+#             */
/*   Updated: 2023/02/21 14:00:13 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_i(int nb, t_struct *tab)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_itoa(nb);
	while (str[i] != '\0')
	{
		ft_putchar(str[i], tab);
		i++;
	}
	free (str);
}

int	ft_print_i(t_struct *tab, va_list *ap)
{
	int		nb;

	nb = va_arg(*ap, int);
	ft_putnbr_i(nb, tab);
	return (0);
}
