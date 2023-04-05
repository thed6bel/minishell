/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:07:13 by lwathar           #+#    #+#             */
/*   Updated: 2022/10/03 16:35:15 by lowathar         ###   ########.fr       */
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

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	j;
	char			*mapi;

	i = 0;
	j = 0;
	if (s == NULL || f == NULL)
		return (ft_protect());
	while (s[i] != '\0')
		i++;
	mapi = malloc(sizeof(char) * (i + 1));
	if (mapi == NULL)
		return (0);
	while (j < i)
	{
		mapi[j] = f(j, s[j]);
		j++;
	}
	mapi[i] = '\0';
	return (mapi);
}
