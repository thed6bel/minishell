/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:29:55 by hucorrei          #+#    #+#             */
/*   Updated: 2022/10/19 13:38:29 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_conv(char *str, long int nbr, int len, int i)
{
	while (len > i)
	{
		len--;
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	int			i;
	long		nbr;

	nbr = n;
	len = ft_intlen(n);
	i = 0;
	if (n < 0 || len == 0)
		len++;
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	if (n < 0)
	{
		nbr *= -1;
		str[0] = '-';
		i++;
	}
	str[len] = '\0';
	str = ft_conv(str, nbr, len, i);
	return (str);
}
