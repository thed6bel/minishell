/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:49:25 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/08 14:56:15 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_numeric_argument(const char *argument)
{
	int						i;
	unsigned long long int	j;

	i = 0;
	j = atoi(argument);
	while (argument[i])
	{	
		if (argument[i] == '+')
			i++;
		if (!ft_isdigit(argument[i]))
		{
			if (argument[i] == '-')
				exit ((j + 255) + 1);
			printf("exit: %s : numeric argument required\n", argument);
			exit(255);
		}
		i++;
	}
	if (j > 9223372036854775807)
	{
		write(1, "exit: ", 6);
		exit(255);
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
	exit(g_status);
}
