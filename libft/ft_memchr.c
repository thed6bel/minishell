/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:52:25 by hucorrei          #+#    #+#             */
/*   Updated: 2022/10/18 10:54:52 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s1;

	s1 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s1[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
