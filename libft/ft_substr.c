/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thed6bel <thed6bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:27:33 by lwathar           #+#    #+#             */
/*   Updated: 2023/05/28 23:51:51 by thed6bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*ft_protect(void)
{
	char	*ptct;
	int		j;

	j = 0;
	ptct = malloc(sizeof(char) * 1);
	if (ptct == NULL)
		return (0);
	ptct[j] = '\0';
	return (ptct);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_protect());
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	s1 = malloc(sizeof(*s) * (len + 1));
	if (s1 != NULL)
	{
		i = 0;
		while (i < len)
		{
			s1[i] = s[i + start];
			i++;
		}
		s1[i] = '\0';
		return (s1);
	}
	return (NULL);
}
