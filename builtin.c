/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:21:47 by hucorrei          #+#    #+#             */
/*   Updated: 2023/05/03 09:32:11 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ctrl_builtin(t_data *cmd)//mon fav
{
	int len;

	//verif si '/' dans la cmd
	if (ft_strchr(cmd->cmd, '/') || ft_strchr(cmd->path, '/'))
		return(0);
	len = ft_strlen(cmd->cmd);
	if ((ft_strncmp(cmd->cmd, "echo", len) == 0) && len == 4)
		return(1);
	if ((ft_strncmp(cmd->cmd, "cd", len) == 0) && len == 2)
		return(1);
	if ((ft_strncmp(cmd->cmd, "pwd", len) == 0) && len == 3)
		return(1);
	if ((ft_strncmp(cmd->cmd, "export", len) == 0) && len == 6)
		return(1);
	if ((ft_strncmp(cmd->cmd, "unset", len) == 0) && len == 5)
		return(1);
	if ((ft_strncmp(cmd->cmd, "env", len) == 0) && len == 3)
		return(1);
	if ((ft_strncmp(cmd->cmd, "exit", len) == 0) && len == 4)
		return(1);
	else
		return(0);
}

//VS

char	*ft_ctrl_builtin(t_data *cmd)
{
	int len;

	//verif si '/' dans la cmd
	if (ft_strchr(cmd->cmd, '/') || ft_strchr(cmd->path, '/'))
		return('adef');//a definir!
	len = ft_strlen(cmd->cmd);
	if ((ft_strncmp(cmd->cmd, "echo", len) == 0) && len == 4)
		return('echo');
		//ou ft_builtin_echo(cmd);
	if ((ft_strncmp(cmd->cmd, "cd", len) == 0) && len == 2)
		return('cd');
		//ou ft_builtin_cd(cmd);
	if ((ft_strncmp(cmd->cmd, "pwd", len) == 0) && len == 3)
		return('pwd');
		//ou ft_builtin_pwd(cmd);
	if ((ft_strncmp(cmd->cmd, "export", len) == 0) && len == 6)
		return('export');
		//ou ft_builtin_export(cmd);
	if ((ft_strncmp(cmd->cmd, "unset", len) == 0) && len == 5)
		return('unset');
		//ou ft_builtin_unset(cmd);
	if ((ft_strncmp(cmd->cmd, "env", len) == 0) && len == 3)
		return('env');
		//ou ft_builtin_env(cmd);
	if ((ft_strncmp(cmd->cmd, "exit", len) == 0) && len == 4)
		return('exit');
		//ou ft_builtin_exit(cmd);
	else
		return('adef');//a definir!
}
