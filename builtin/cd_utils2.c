/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:27:08 by thed6bel          #+#    #+#             */
/*   Updated: 2023/06/16 11:07:39 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_directory(char *homedir, t_env *envp)
{
	char	*cur_dir;
	t_env	*old;
	t_env	*new;

	cur_dir = getcwd(NULL, 0);
	old = envp;
	new = envp;
	if (cur_dir == NULL)
	{
		chdir(homedir);
		printf("minishell: cd: DIR: No such file or directory\n");
		g_status = 0;
	}
	else if (chdir(homedir) == -1)
	{
		printf("minishell: cd: %s: %s\n", homedir, strerror(errno));
		g_status = 1;
		free(cur_dir);
	}
	else
	{
		ft_upd_pwd(old, new);
		free(cur_dir);
	}
}
