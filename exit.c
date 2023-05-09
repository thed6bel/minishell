/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thed6bel <thed6bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:22:55 by thed6bel          #+#    #+#             */
/*   Updated: 2023/05/08 20:38:50 by thed6bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int g_status;

void	built_exit(t_data *cmd, t_env *envp)
{
    int i;
    int mod;

    i = 0;
    mod = 0;
    if (cmd->cmd[1] != NULL)
    {
        while (cmd->cmd[1][i])
            if (!ft_isdigit(cmd->cmd[1][i++]))
                //ft_error("bad argument");
        if (cmd->cmd[1][i] == '\0')
        {
            g_status = ft_atoi(cmd->cmd[1]);
            mod = 1;
        }
    }
    if (cmd->cmd[1] != NULL && cmd->cmd[2] != NULL)
        //ft_error("too many argument");
    ft_free_env(envp);
    if (mod == 0)
        g_status = 0;
    exit(g_status);
        
}
