/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:32:54 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/01 14:06:44 by hucorrei         ###   ########.fr       */
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

void	ft_op_utils(t_env *oldpwd_e, t_env *pwd_e, t_env *tmp, t_env *envp)
{
	oldpwd_e = (t_env *)malloc(sizeof(t_env));
	if (!oldpwd_e)
		return ;
	oldpwd_e->var = ft_strdup("OLDPWD");
	oldpwd_e->equal = '=';
	if (pwd_e)
		oldpwd_e->value = ft_strdup(pwd_e->value);
	else
		oldpwd_e->value = ft_strdup("");
	oldpwd_e->next = NULL;
	if (!tmp)
		tmp = envp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = oldpwd_e;
}

void	ft_make_oldpwd(t_env *envp)
{
	t_env	*tmp;
	t_env	*pwd_element;
	t_env	*oldpwd_element;

	tmp = envp;
	pwd_element = NULL;
	oldpwd_element = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PWD", 3) == 0)
			pwd_element = tmp;
		else if (ft_strncmp(tmp->var, "OLDPWD", 6) == 0)
			oldpwd_element = tmp;
		if (oldpwd_element && pwd_element)
			break ;
		tmp = tmp->next;
	}
	if (!oldpwd_element)
		ft_op_utils(oldpwd_element, pwd_element, tmp, envp);
}
