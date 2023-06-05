/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thed6bel <thed6bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:27:08 by thed6bel          #+#    #+#             */
/*   Updated: 2023/06/04 18:38:46 by thed6bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		perror(homedir);
		g_status = 1;
		free(cur_dir);
	}
	else
	{
		ft_upd_pwd(old, new);
		free(cur_dir);
	}
}
