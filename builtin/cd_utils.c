/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:32:54 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/01 13:33:42 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_oldpwd(t_env *envp)
{
	t_env	*tmp;
	char	*oldpwd;

	tmp = envp;
	while (tmp != NULL && ft_strncmp(tmp->var, "OLDPWD", 6) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	oldpwd = ft_strdup(tmp->value);
	if (!oldpwd)
		return (NULL);
	printf("%s\n", oldpwd);
	return (oldpwd);
}

void	get_old_dir(t_env *envp)
{
	char	*old_dir;

	old_dir = get_oldpwd(envp);
	if (!old_dir)
	{
		printf("cd: OLDPWD not set\n");
		g_status = 1;
		return ;
	}
	else if (old_dir && chdir(old_dir) != -1)
		ft_upd_pwd(envp);
	else
		g_status = 1;
	free(old_dir);
}

void	ft_make_oldpwd(t_env *envp)
{
	t_env	*new;
	char	*oldpwd;

	new = envp;
	while (new != NULL && ft_strncmp(new->var, "PWD", 3) != 0)
		new = new->next;
	oldpwd = ft_strdup(new->value);
	t_env	*old = malloc(sizeof(t_env));
	old->var = ft_strdup("OLDPWD");
	old->value = oldpwd;
	old->next = envp;
	envp = old;
}
