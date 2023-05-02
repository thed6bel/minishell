/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thed6bel <thed6bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:38:14 by thed6bel          #+#    #+#             */
/*   Updated: 2023/05/01 15:46:08 by thed6bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
ne pas oublier une fonction qui copie le double tab de **env vers liste chain2e
et l'inverse pour envoyer un double tableau vers execve
*/

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
    while (new->value[0][i])
	{
		ret[i] = new->value[0][i];
		i++;
	}
	ret[i] = '\0';
    old->value[0] = ret;
    free(new->value[0]);
    new->value[0] =  getcwd(NULL, 0);
}



void    ft_builtin_cd(t_data *cmd, t_env *envp)
{
    if (cmd->cmd[1] == NULL)
        return;//ou ft_error?
    //voir si afdfichage msg erreur?
    if (chdir(cmd->cmd[1]) != -1)
        ft_upd_pwd(envp);
    //gstatus = 0
    else
    {
        //gstatus = verifier le code exit en cas erreur;
    }
    //ont met un pointeur sur envp pour recupere la nouvelle valeur
}

//test semble ok a ctrl quand meme!!!
