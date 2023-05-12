/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:07:31 by lwathar           #+#    #+#             */
/*   Updated: 2022/10/14 14:13:07 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(char const *str, char c)
{
	int	a;
	int	size;

	a = 0;
	size = 0;
	while (str[a] != '\0')
	{
		if (str[a] != c)
		{
			while (str[a] != c && str[a])
				a++;
			size++;
		}
		else if (str[a] == c)
			a++;
	}
	return (size);
}

static char	**ft_bugfree(char **split, const char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = ft_size(str, c);
	while (i < j)
	{
		if (split[i] == NULL)
		{
			i = 0;
			while (i < j)
			{
				free(split[i]);
				i++;
			}
			free (split);
			return (NULL);
		}
		i++;
	}
	return (split);
}

static void	ft_write_char(char *dest, const char *src, char c)
{
	int	j;

	j = 0;
	while (src[j] != c && src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
}

static void	*ft_split_fil(char **split, const char *str, char c)
{
	int	a;
	int	b;
	int	i;

	i = 0;
	a = 0;
	while (str[a] != '\0')
	{
		if (str[a] == c)
			a++;
		else
		{
			b = 0;
			while (str[a + b] != c && str[a + b])
				b++;
			split[i] = (char *)malloc(sizeof(char) * (b + 1));
			if (split[i] == NULL)
				return (NULL);
			ft_write_char(split[i], str + a, c);
			a = a + b;
			i++;
		}
	}
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	char	**split;
	int		i;

	if (str == NULL)
		return (NULL);
	i = ft_size(str, c);
	split = (char **)malloc(sizeof(char *) * (i + 1));
	if (split == NULL)
		return (0);
	split[i] = 0;
	ft_split_fil(split, str, c);
	return (ft_bugfree(split, str, c));
}
