/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:40:30 by hucorrei          #+#    #+#             */
/*   Updated: 2023/02/01 14:07:04 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printptr(unsigned long ptr)
{
	int	print_len;

	print_len = 0;
	print_len += write(1, "0x", 2);
	if (ptr == 0)
	{
		print_len += write(1, "0", 1);
	}
	else
	{
		ft_putptr(ptr);
		print_len += ft_ptrlen(ptr);
	}
	return (print_len);
}

int	ft_ptrlen(unsigned long nbr)
{
	int	len;

	len = 0;
	while (nbr)
	{
		len++;
		nbr = nbr / 16;
	}
	return (len);
}

void	ft_putptr(unsigned long nbr)
{
	if (nbr >= 16)
	{
		ft_putptr(nbr / 16);
		ft_putptr(nbr % 16);
	}
	else
	{
		if (nbr <= 9)
			ft_printchar(nbr + '0');
		else
			ft_printchar(nbr - 10 + 'a');
	}
}
