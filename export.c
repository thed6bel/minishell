/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thed6bel <thed6bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:44:14 by thed6bel          #+#    #+#             */
/*   Updated: 2023/05/01 23:14:18 by thed6bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char ft_set_var(char *arg)
{

}

char ft_set_key(char *arg)
{

}

void    ft_new_list(var, value, buff)
{

}

void    ft_print_export(t_data *cmd, t_env *envp)
{
    
}

void	built_export(t_data *cmd, t_env *envp)
{
    t_env *buff;
    char *var;
    char *value;

    buff = envp;
    //protec NULL return
    if (cmd->cmd[1] == NULL)
        ft_print_export(cmd, envp); //declare -x PWD="/home/thed6bel/projet/test/minishell/louis/minishell" sous linux
    var = ft_set_var(cmd->cmd[1]);
    value = ft_set_key(cmd->cmd[1]);
    //ctrl erreur dans nom si il y en a
    while (buff != NULL)
        buff = buff->next;
    if (buff == NULL)
        ft_new_list(var, value, buff);
    free(var);
    free(value);
    
    
}
