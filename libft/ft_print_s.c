/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:57:35 by lowathar          #+#    #+#             */
/*   Updated: 2023/02/21 13:59:52 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_s(t_struct *tab, va_list *ap)
{
	char	*str;
	int		i;

	i = 0;
	str = va_arg(*ap, char *);
	if (!str)
		str = "(null)";
	while (str[i])
	{
		ft_putchar(str[i], tab);
		i++;
	}
	return (0);
}
