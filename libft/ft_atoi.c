/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:18:57 by hucorrei          #+#    #+#             */
/*   Updated: 2022/10/21 11:21:22 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int						i;
	int						signe;
	unsigned long long int	nbr;

	i = 0;
	signe = 1;
	nbr = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f' )
		i++;
	while (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
		if (nptr[i] == '-' || nptr[i] == '+')
			return (0);
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nbr = nptr[i++] - '0' + (nbr * 10);
	if (nbr > 9223372036854775807 && signe == 1)
		return (-1);
	if (nbr > 9223372036854775807 && signe == -1)
		return (0);
	return (signe * nbr);
}
