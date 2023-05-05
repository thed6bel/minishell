/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:47:35 by hucorrei          #+#    #+#             */
/*   Updated: 2023/05/02 14:44:16 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtin_pwd(t_data *cmd)
{
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	write(cmd->fd_out, cwd, ft_strlen(cwd));
	write(cmd->fd_out, "\n", 1);
	free(cwd);
	//set variable globale de status
}
/*test semble ok

VS :

void	ft_builtin_pwd(void)
{
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	free(cwd);
	//set variable globale de status
}
*/