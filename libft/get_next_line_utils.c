/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:55:52 by hucorrei          #+#    #+#             */
/*   Updated: 2023/02/02 10:04:52 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_GNL(char *s)
{
	if (!s)
		return (0);
	while (*s != '\0' && *s != '\n')
		s++;
	if (*s == '\n')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin_GNL(char *lstr, char *buff)
{
	ssize_t	i;
	ssize_t	j;
	char	*str;

	if (!lstr)
	{
		lstr = malloc(1);
		if (!lstr)
			return (NULL);
		lstr[0] = '\0';
	}
	str = malloc(sizeof(char) * ((ft_strlen_GNL(lstr) + ft_strlen_GNL(buff)) + 1));
	if (!str)
		return (ft_free(&lstr));
	i = -1;
	j = 0;
	if (lstr)
		while (lstr[++i] != '\0')
			str[i] = lstr[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(lstr) + ft_strlen(buff)] = '\0';
	free(lstr);
	return (str);
}

size_t	ft_strlen_GNL(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_getline(char *lstr)
{
	int		i;
	char	*str;

	i = 0;
	if (!lstr[i])
		return (NULL);
	while (lstr[i] && lstr[i] != '\n')
		i++;
	str = malloc(i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (lstr[i] && lstr[i] != '\n')
	{
		str[i] = lstr[i];
		i++;
	}
	if (lstr[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*ft_newlstr(char *lstr)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (lstr[i] && lstr[i] != '\n')
		i++;
	if (!lstr[i])
	{
		free(lstr);
		return (NULL);
	}
	str = malloc(ft_strlen(lstr) - i + 1);
	if (!str)
	{
		free(lstr);
		return (NULL);
	}
	i++;
	j = 0;
	while (lstr[i])
		str[j++] = lstr[i++];
	str[j] = '\0';
	free(lstr);
	return (str);
}
