/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:06:48 by lwathar           #+#    #+#             */
/*   Updated: 2022/10/03 16:35:19 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_protect(void)
{
	char	*ptct;

	ptct = malloc(sizeof(char) * 1);
	if (ptct == NULL)
		return (0);
	ptct[0] = '\0';
	return (ptct);
}

static int	char_in_set(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		start;
	int		end;
	int		i;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (ft_protect());
	while (char_in_set(s1[i], (char *)set) && s1[i])
		i++;
	start = i;
	i = (ft_strlen(s1) - 1);
	while (char_in_set(s1[i], (char *)set) && i > start)
		i--;
	end = i;
	i = 0;
	new = (char *)malloc((end - start + 2) * sizeof(char));
	if (new == NULL)
		return (new);
	while (start <= end)
		new[i++] = s1[start++];
	new[i] = 0;
	return (new);
}
