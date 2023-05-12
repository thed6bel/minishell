/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thed6bel <thed6bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:44:46 by lowathar          #+#    #+#             */
/*   Updated: 2023/04/07 19:48:29 by thed6bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_ui(unsigned int nb, t_struct *tab)
{
	if (nb <= 9)
		ft_putchar(nb + 48, tab);
	else if (nb > 9)
	{
		ft_putnbr_ui(nb / 10, tab);
		ft_putnbr_ui(nb % 10, tab);
	}
	else
	{
		ft_putchar('-', tab);
		ft_putnbr_ui(nb * -1, tab);
	}
}

int	ft_print_u(t_struct *tab, va_list *ap)
{
	int	nb;

	nb = va_arg(*ap, unsigned int);
	ft_putnbr_ui(nb, tab);
	return (0);
}
