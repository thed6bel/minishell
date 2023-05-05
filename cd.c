/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:52:17 by hucorrei          #+#    #+#             */
/*   Updated: 2023/05/04 13:51:42 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int g_status;
/*
ne pas oublier une fonction qui copie le double tab de **env vers liste chain2e
et l'inverse pour envoyer un double tableau vers execve
*/

char	*ft_gethomedir(t_env *envp)
{
	char *homedir;
	t_env *tmp;
	int i;

	tmp = envp;
	i = 0;
	while (tmp != NULL && ft_strncmp(tmp->var, "HOME", 6) != 0)
		tmp = tmp->next;
	homedir = malloc(sizeof(char) * (ft_strlen(tmp->value[0]) + 1));
	if (!homedir)
		return(NULL);//ou ft_error
	while (tmp->value[i] != '\0')
	{
		homedir[i] = tmp->value[i];
		i++;
	}
	homedir[i] = '\0';
	return (homedir);
}

void    ft_upd_pwd(t_env *envp)
{
	t_env *old;
	t_env *new;
	char	*ret;
	int	i;

	old = envp;
	new = envp;
	i = 0;
	while (old != NULL && ft_strncmp(old->var, "OLDPWD", 6) != 0)
		old = old->next;
	while (new != NULL && ft_strncmp(new->var, "PWD", 3) != 0)
		new = new->next;
	free(old->value[0]);
	ret = malloc(sizeof(char) * (ft_strlen(new->value[0]) + 1));
	if (!ret)
		return ;
	while (new->value[i] != '\0')
	{
		ret[i] = new->value[i];
		i++;
	}
	ret[i] = '\0';
	old->value[0] = ret;
	free(ret);
	free(new->value[0]);
	new->value[0] =  getcwd(NULL, 0);
}



void    ft_builtin_cd(t_data *cmd, t_env *envp)
{
	char *homedir;
	
	homedir = NULL;
	if (cmd->cmd[1] == NULL || ft_strncmp(cmd->cmd[1], "~", 1) != 0)
	{
		homedir = ft_gethomedir(envp);
		if (chdir(homedir) != -1)
		{
			ft_upd_pwd(envp);
			g_status = 0;   
		}
	}
		//error, voir si afdfichage msg erreur?
	else if (chdir(cmd->cmd[1]) != -1)
	{
		ft_upd_pwd(envp);
		g_status = 0;   
	}
	else
		g_status = 1; //mais verifier le code exit en cas erreur;
	//ont met un pointeur sur envp pour recupere la nouvelle valeur
}

/*gerer le :
~ :r2cuperer le dossier HOME dans la liste chaine ? mais c'est un raccourci pas un chemin relatif ou absolue??
cd sans rien = vers les repertoire user/home ? mais ce n'est pas un chemin relatif ou absolue??

a tester de nouveau car changement de **value a *value!!!!!!!!!!!!!!!
*/