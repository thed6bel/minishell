/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:04:19 by hucorrei          #+#    #+#             */
/*   Updated: 2022/10/25 10:04:51 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	size_t	i;
	void	*ptr;

	i = (nitems * size);
	ptr = malloc(i);
	if (ptr == NULL)
		return (0);
	ft_bzero(ptr, i);
	return (ptr);
}
