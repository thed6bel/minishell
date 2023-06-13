/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:49:25 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/13 14:47:22 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_atoi2(const char *nptr, long long int *n)
{
	int						i;
	int						signe;
	unsigned long long int	nbr;

	i = 0;
	signe = 1;
	nbr = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
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
	if (((nbr > 9223372036854775808ULL) && signe == -1) || \
		((nbr > 9223372036854775807) && signe == 1))
		return (0);
	*n = (long long int)(nbr * signe);
	return (1);
}

void	handle_numeric_argument(const char *arg)
{
	int					i;
	long long int		j;

	i = 0;
	if (!ft_atoi2(arg, &j))
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n", arg);
		exit(255);
	}
	while (arg[i])
	{	
		if (arg[i] == '+')
			i++;
		if (!ft_isdigit(arg[i]))
		{
			if (arg[i] == '-')
				exit ((j + 255) + 1);
			printf("exit\nminishell: %s: numeric argument required\n", arg);
			exit(255);
		}
		i++;
	}
}

void	ft_builtin_exit(t_mini *n, t_env *env_list)
{
	if (n->full_cmd[1] != NULL)
	{
		handle_numeric_argument(n->full_cmd[1]);
		g_status = atoi(n->full_cmd[1]);
	}
	if (n->full_cmd[1] != NULL && n->full_cmd[2] != NULL)
	{
		write(1, "exit: too many arguments\n", 25);
		exit(1);
	}
	if (n->full_cmd[1] == NULL)
		g_status = 0;
	free_env_list(env_list);
	system("leaks minishell");
	exit(g_status);
}

