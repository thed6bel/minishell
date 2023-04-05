/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:27:33 by lwathar           #+#    #+#             */
/*   Updated: 2022/10/04 14:44:01 by lowathar         ###   ########.fr       */
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

	s1 = NULL;
	i = 0;
	if (s == 0 || start > ft_strlen(s))
		return (ft_protect());
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	s1 = malloc(sizeof(*s) * (len + 1));
	if (s1 != NULL)
	{
		while (i < len && i < ft_strlen(s))
		{
			s1[i] = s[i + start];
			i++;
		}
		s1[i] = '\0';
		return (s1);
	}
	return (NULL);
}
