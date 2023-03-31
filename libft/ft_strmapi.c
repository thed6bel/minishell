/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:55:50 by hucorrei          #+#    #+#             */
/*   Updated: 2022/10/18 09:53:57 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*str;
	unsigned int		i;

	i = 0;
	if (!f)
		return ((char *)s);
	str = ft_strdup(s);
	if (!str)
		return (0);
	while (str[i])
	{
		str[i] = (*f)(i, str[i]);
		i++;
	}
	return (str);
}
