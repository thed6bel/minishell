/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:18:02 by lwathar           #+#    #+#             */
/*   Updated: 2022/10/04 14:10:11 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		len;

	len = ft_strlen(s);
	ptr = (char *)s + len - 1;
	if (c == '\0')
		return (ptr + 1);
	while (len > 0)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr--;
		len--;
	}
	if (c == '\0')
	{
		ptr++;
		return (ptr);
	}
	return (NULL);
}
