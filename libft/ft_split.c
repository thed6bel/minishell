/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:24:56 by hucorrei          #+#    #+#             */
/*   Updated: 2023/02/01 14:05:12 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

static int	ft_len(char const *s, char c, int i)
{
	int	len;

	len = 0 ;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

static char	*ft_write(char const *s, char c, int i)
{
	int		j;
	char	*res;

	j = 0;
	res = malloc(sizeof(char) * (ft_len(s, c, i) + 1));
	if (!res)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!res)
		return (NULL);
	while (j < ft_count(s, c))
	{
		while (s[i] == c)
			i++;
		res[j] = ft_write(s, c, i);
		if (!res[j])
			return ((char **)ft_free(res));
		while (s[i] != c && s[i] != '\0')
			i++;
		j++;
	}
	res[j] = NULL;
	return (res);
}
