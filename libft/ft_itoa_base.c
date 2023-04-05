/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:23:36 by lwathar           #+#    #+#             */
/*   Updated: 2023/03/28 13:04:19 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sizebase(unsigned long long nbr, int b_size)
{
	int		i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / b_size;
		i++;
	}
	return (i);
}

char	*ft_itoa_base(unsigned long long n, char *base, int b_size)
{
	char	*str;
	int		size;

	size = ft_sizebase(n, b_size);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (--size >= 0)
	{
		str[size] = base[n % b_size];
		n = n / b_size;
	}
	return (str);
}
