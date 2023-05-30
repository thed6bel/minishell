/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:49:25 by hucorrei          #+#    #+#             */
/*   Updated: 2023/05/30 10:57:04 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtin_exit(t_mini *n, t_env *env_list)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	if (n->full_cmd[1] != NULL)
	{
		while (n->full_cmd[1][i[0]])
			if (!ft_isdigit(n->full_cmd[1][i[0]++]))
			{
				printf("exit: %s: numeric argument required\n", n->full_cmd[1]);
				exit(255);
			}
		if (n->full_cmd[1][i[0]] == '\0')
		{
			g_status = ft_atoi(n->full_cmd[1]);
			i[1] = 1;
		}
	}
	if (n->full_cmd[1] != NULL && n->full_cmd[2] != NULL)
	{
		printf("exit: too many arguments\n");
		exit(1);
	}
	if (i[1] == 0)
		g_status = 0;
	//printf("gstatus = %d\n", g_status);
	system("leaks a.out");
	free_env_list(env_list);
	exit(g_status);
}
