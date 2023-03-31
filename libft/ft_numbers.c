/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:32:22 by hucorrei          #+#    #+#             */
/*   Updated: 2023/02/01 14:06:50 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	ft_putnbr(int n)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(1, "-2147483648", 11);
			return ;
		}
		ft_printchar('-');
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_printchar(n + 48);
}

void	ft_putunsigned(unsigned int n)
{
	if (n >= 10)
	{
		ft_putunsigned(n / 10);
		ft_putunsigned(n % 10);
	}
	else
		ft_printchar(n + 48);
}

int	ft_printunsigned(unsigned int n)
{
	int	print_len;

	ft_putunsigned(n);
	print_len = 0;
	if (n == 0)
		print_len += 1;
	while (n)
	{
		n /= 10;
		print_len++;
	}
	return (print_len);
}
