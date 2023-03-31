/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printtools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:42:07 by hucorrei          #+#    #+#             */
/*   Updated: 2023/02/01 14:07:08 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		i = 6;
		return (i);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_printnbr(int n)
{
	int	print_len;

	print_len = 0;
	ft_putnbr(n);
	if (n <= 0)
		print_len += 1;
	while (n)
	{
		n /= 10;
		print_len++;
	}
	return (print_len);
}

int	ft_printpercent(void)
{
	write(1, "%", 1);
	return (1);
}
