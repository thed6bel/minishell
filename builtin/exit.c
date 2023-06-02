/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:49:25 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/02 10:53:46 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_numeric_argument(const char *argument)
{
	int	i;

	i = 0;
	while (argument[i])
	{
		if (!ft_isdigit(argument[i]))
		{
			write(1, "exit: ", 6);
			write(1, argument, ft_strlen(argument));
			write(1, ": numeric argument required\n", 28);
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
	system("leaks minishell");//a retirer//
	free_env_list(env_list);
	exit(g_status);
}
