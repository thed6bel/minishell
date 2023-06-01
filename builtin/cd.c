/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:52:17 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/01 13:33:24 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_compet_path(char *cmd, t_env *envp)
{
	char	*home;
	char	*completpath;
	int		i;
	int		j;

	i = 0;
	j = 1;
	home = ft_gethomedir(envp);
	completpath = malloc(ft_strlen(home) + ft_strlen(cmd));
	if (!completpath)
		return (NULL);
	while (home[i])
	{
		completpath[i] = home[i];
		i++;
	}
	while (cmd[j])
	{
		completpath[i] = cmd[j];
		i++;
		j++;
	}
	completpath[i] = '\0';
	free(home);
	return (completpath);
}

char	*ft_gethomedir(t_env *envp)
{
	char	*homedir;
	t_env	*tmp;
	int		i;

	tmp = envp;
	i = 0;
	while (tmp != NULL && ft_strncmp(tmp->var, "HOME", 5) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	homedir = malloc(sizeof(char) * (ft_strlen(tmp->value) + 1));
	if (!homedir)
		return (NULL);
	while (tmp->value[i] != '\0')
	{
		homedir[i] = tmp->value[i];
		i++;
	}
	homedir[i] = '\0';
	return (homedir);
}

static void	ft_upd_pwd(t_env *envp)
{
	t_env	*old;
	t_env	*new;
	char	*ret;
	int		i;

	old = envp;
	new = envp;
	i = -1;
	ft_make_oldpwd(envp);
	while (old != NULL && ft_strncmp(old->var, "OLDPWD", 6) != 0)
		old = old->next;
	while (new != NULL && ft_strncmp(new->var, "PWD", 3) != 0)
		new = new->next;
	ret = malloc(sizeof(char) * (ft_strlen(new->value) + 1));
	if (!ret)
		return ;
	while (new->value[++i] != '\0')
		ret[i] = new->value[i];
	free(old->value);
	ret[i] = '\0';
	old->value = ret;
	free(new->value);
	new->value = getcwd(NULL, 0);
	g_status = 0;
}


void	ft_builtin_cd(t_mini *n, t_env *envp)
{
	char	*homedir;

	homedir = NULL;
	if (n->full_cmd[1] == NULL || !ft_strncmp(n->full_cmd[1], "~", 1))
	{
		if (n->full_cmd[1])
			homedir = ft_compet_path(n->full_cmd[1], envp);
		else
			homedir = ft_gethomedir(envp);
		if (chdir(homedir) != -1)
			ft_upd_pwd(envp);
		else
			g_status = 1;
	}
	else if (!ft_strncmp(n->full_cmd[1], "-", 1))
		return (get_old_dir(envp));
	else if (chdir(n->full_cmd[1]) != -1)
		ft_upd_pwd(envp);
	else
		g_status = 1;
	if (g_status == 1)
		printf("No such file or directory\n");
	free(homedir);
}
