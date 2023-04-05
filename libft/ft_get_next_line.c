/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:31:51 by lowathar          #+#    #+#             */
/*   Updated: 2023/03/28 13:06:19 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_next2(char *lstr, char *str, int i)
{
	int	j;

	if (!str)
	{
		free(lstr);
		return (NULL);
	}
	i++;
	j = 0;
	while (lstr[i])
	{
		str[j] = lstr[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_next(char *lstr)
{
	char	*str;
	int		i;

	i = 0;
	while (lstr[i] && lstr[i] != '\n')
		i++;
	if (!lstr[i])
	{
		free(lstr);
		return (NULL);
	}
	str = malloc(sizeof(char) * ft_strlen_gnl(lstr) - i + 1);
	ft_next2(lstr, str, i);
	free (lstr);
	return (str);
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
	str = malloc(sizeof(char) * (i + 2));
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

char	*ft_read_file(int fd, char *lstr)
{
	char	*buf;
	int		i;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	i = 1;
	while (!ft_strchr_gnl(lstr) && i != 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(buf);
			free(lstr);
			return (NULL);
		}
		buf[i] = '\0';
		lstr = ft_strjoin_gnl(lstr, buf);
	}
	free(buf);
	return (lstr);
}

char	*get_next_line(int fd)
{
	static char		*lstr;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX - 1)
		return (NULL);
	lstr = ft_read_file(fd, lstr);
	if (!lstr)
		return (NULL);
	line = ft_getline(lstr);
	lstr = ft_next(lstr);
	return (line);
}
