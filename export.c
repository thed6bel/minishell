/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:44:14 by thed6bel          #+#    #+#             */
/*   Updated: 2023/05/03 15:15:10 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int g_status;

char *ft_set_var(char *arg)
{
	int i;
	int size;
	char *res;

	i = 0;
	size = 0;
	while (arg[size] && arg[size] != '=')
		size++;
	if (!arg[size])
		ft_error("not a valide command, use : export [name=value]");
		//return (NULL);
	res = malloc(sizeof(char) * size + 1);
	if (!res)
		return (NULL);
	while (i < size)
	{
		res[i] = arg[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char ft_set_value(char *arg)
{
	int i;
	int size;
	char *res;
	char *tmp;

	i = 0;
	size = 0;
	tmp = arg;
	while(*tmp && *tmp != '=')
		tmp++;
	if (*tmp == '=')
		tmp++;
	while (tmp[size])
		size++;
	res = malloc(sizeof(char *) * size +1);
	if (!res)
		return(NULL);
	while (i , size)
	{
		res[i] = tmp[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void    ft_new_list(char *var, char *value, t_env *buff)
{
	t_env *tmp;
	t_env *new;

	tmp = buff;
	while (tmp != NULL)
		tmp = tmp->next;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	tmp->next = new;
	new->next = NULL;
	new->var = var;
	new->value = value;
	new->equal = '=';
}

void    ft_print_export(t_data *cmd, t_env *envp)
{
	//prendre envp et le mettre par ordre alpha!!
}

void	built_export(t_data *cmd, t_env *envp)
{
	t_env *buff;
	char *var;
	char *value;
	int i;

	buff = envp;
	i = 1;
	//protec NULL return
	if (cmd->cmd[i] == NULL)
		ft_print_export(cmd, envp); //declare -x PWD="/home/thed6bel/projet/test/minishell/louis/minishell" sous linux pareil sous bash
	else
		while (cmd->cmd[i])
		{
			var = ft_set_var(cmd->cmd[i]);
			value = ft_set_value(cmd->cmd[i]);
			//ctrl erreur dans nom si il y en a
			while (buff != NULL)
				buff = buff->next;
			if (buff == NULL)
				ft_new_list(var, value, buff);
			free(var);
			free(value);
		}
	
}

/*
print export faut trier par ordre alpha
pas gerer export var (sans = valeur)

*/
