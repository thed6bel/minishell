/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:41:04 by hucorrei          #+#    #+#             */
/*   Updated: 2023/05/05 15:09:29 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
extern int g_status;

void	built_env(t_data *cmd, t_env *envp)
{
	t_env *buff;

	buff = envp;
	while (buff->next != NULL)
	{
		write(cmd->fd_out, buff->var, ft_strlen(buff->var));
		write(cmd->fd_out, "=", 1);
		write(cmd->fd_out, buff->value, ft_strlen(buff->value));
		write(cmd->fd_out, "\n", 1);
		buff = buff->next;
	}
	if (envp != NULL)
		g_status = 0;
}

/*
OK mais faut pousser les test exp 'var' vs 'var=' s'affiche pas pareille

*/