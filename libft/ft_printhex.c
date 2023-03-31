/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:51:00 by hucorrei          #+#    #+#             */
/*   Updated: 2023/02/01 14:07:00 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhex(unsigned int nbr, char format)
{
	if (nbr == 0)
		return (write(1, "0", 1));
	else
		ft_puthex(nbr, format);
	return (ft_hexlen(nbr));
}

int	ft_hexlen(unsigned	int nbr)
{
	int	len;

	len = 0;
	while (nbr)
	{
		nbr /= 16;
		len++;
	}
	return (len);
}

void	ft_puthex(unsigned int num, char format)
{
	if (num >= 16)
	{
		ft_puthex(num / 16, format);
		ft_puthex(num % 16, format);
	}
	else
	{
		if (num <= 9)
			ft_printchar((num + '0'));
		else
		{
			if (format == 'x')
				ft_printchar((num - 10 + 'a'));
			else
				ft_printchar((num - 10 + 'A'));
		}
	}
}
