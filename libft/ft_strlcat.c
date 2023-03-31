/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:06:38 by hucorrei          #+#    #+#             */
/*   Updated: 2022/10/17 14:24:29 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (n <= ft_strlen(dst))
		return (n + ft_strlen(src));
	i = ft_strlen(dst);
	k = i;
	j = 0;
	while (src[j] != '\0' && i < (n - 1))
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (k + ft_strlen(src));
}
