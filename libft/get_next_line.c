/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:55:43 by hucorrei          #+#    #+#             */
/*   Updated: 2023/02/02 10:05:45 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char			*line;
	static char		*lstr[FOPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX - 1)
		return (NULL);
	lstr[fd] = ft_readstr(fd, lstr[fd]);
	if (!lstr[fd])
		return (NULL);
	line = ft_getline(lstr[fd]);
	lstr[fd] = ft_newlstr(lstr[fd]);
	return (line);
}

char	*ft_readstr(int fd, char *lstr)
{
	char	*buff;
	int		read_byte;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	read_byte = 1;
	while (!ft_strchr_GNL(lstr) && read_byte != 0)
	{
		read_byte = read(fd, buff, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buff);
			free(lstr);
			return (NULL);
		}
		buff[read_byte] = '\0';
		lstr = ft_strjoin_GNL(lstr, buff);
	}
	free(buff);
	return (lstr);
}

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}
