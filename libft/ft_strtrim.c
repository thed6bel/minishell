/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:15:43 by hucorrei          #+#    #+#             */
/*   Updated: 2022/10/18 11:47:57 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*copy;
	int		i;
	int		j;
	int		len;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1);
	while (j >= 0 && ft_strrchr(set, s1[j]))
		j--;
	len = (j - i) + 1;
	copy = ft_substr((char *)s1, i, len);
	return (copy);
}
