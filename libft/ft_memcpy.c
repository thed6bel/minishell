/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:37:20 by hucorrei          #+#    #+#             */
/*   Updated: 2022/10/21 13:43:09 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*s1;
	char	*d1;

	i = 0;
	s1 = (char *)src;
	d1 = (char *)dest;
	if (!src && !dest)
		return (0);
	while (i < n)
	{
		d1[i] = s1[i];
		i++;
	}
	return (dest);
}
