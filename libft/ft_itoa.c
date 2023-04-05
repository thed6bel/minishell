/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:20:41 by lwathar           #+#    #+#             */
/*   Updated: 2022/10/13 12:43:47 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_size_array(int n)
{
	int		nb;

	nb = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		nb++;
	}
	return (nb);
}

static void	set_array(char *nbr, int n, int neg, int size_array)
{
	while (size_array + neg > 0)
	{
		nbr[(size_array + neg) - 1] = (n % 10) + 48;
		n /= 10;
		size_array--;
	}
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		neg;
	int		size_array;

	neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		neg = 1;
		n *= -1;
	}
	size_array = set_size_array(n);
	nbr = malloc(sizeof(char) * (size_array + neg + 1));
	if (nbr == NULL)
		return (NULL);
	nbr[size_array + neg] = '\0';
	set_array(nbr, n, neg, size_array);
	if (neg == 1)
		nbr[0] = '-';
	return (nbr);
}
