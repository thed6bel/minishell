/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:44:14 by thed6bel          #+#    #+#             */
/*   Updated: 2023/05/05 13:46:31 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TEST ok sans leaks cf testexport
#include "../minishell.h"

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
		return(arg);
    if (size == 0)
        return (NULL);
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

char *ft_set_value(char *arg)
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
    else
        return (NULL);
	while (tmp[size])
		size++;
	res = malloc(sizeof(char *) * size +1);
	if (!res)
		return(NULL);
	while (i < size)
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
	new = malloc(sizeof(t_env));
	if (!new)
		return;
	tmp->next = new;
	new->next = NULL;
	new->var = var;
    if (value)
	    new->equal = '=';
	new->value = value;    
	//printf("NEW LIST END : %s%c%s\n", new->var, new->equal, new->value);
}

void	ft_swap_env(t_env *env1, t_env *env2)
{
	char *var_tmp;
	char equal_tmp;
	char **value_tmp;
	
	var_tmp = env1->var;
    equal_tmp = env1->equal;
    value_tmp = env1->value;

    env1->var = env2->var;
    env1->equal = env2->equal;
    env1->value = env2->value;

    env2->var = var_tmp;
    env2->equal = equal_tmp;
    env2->value = value_tmp;	
}

void	ft_sort_list(t_env *envpcpy)
{
	int swap;
	t_env *tmp;
	t_env *list;

	list = NULL;
	swap = 1;
	while (swap)
	{
		swap = 0;
		tmp = envpcpy;
		while (tmp->next != list)
		{
			if (ft_strncmp(tmp->var, tmp->next->var, ft_strlen(tmp->var) + 1) > 0)
			{
				ft_swap_env(tmp, tmp->next);
				swap = 1;	
			}
			tmp = tmp->next;
		}
		list = tmp;
	}
}

void ft_print_export(t_data *cmd, t_env *envp)
{
	//prendre envp et le mettre par ordre alpha!!
	t_env *envpcpy;
	t_env *tmp;
	t_env *new_env;

	envpcpy = NULL;
	tmp = NULL;
	new_env = NULL;

	while (envp)
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			return;
		new_env->var = ft_strdup(envp->var);
		new_env->equal = envp->equal;
		new_env->value = envp->value ? ft_strdup(envp->value) : NULL;
		new_env->next = NULL;
		if (envpcpy == NULL)
		{
			envpcpy = new_env;
			tmp = new_env;
		}
		else
		{
			tmp->next = new_env;
			tmp = tmp->next;
		}
		envp = envp->next;
	}
	ft_sort_list(envpcpy);
	while (envpcpy)
	{
		write(cmd->fd_out, "declare -x ", 11);
		write(cmd->fd_out, envpcpy->var, ft_strlen(envpcpy->var));
		if (envpcpy->value)
		{
			write(cmd->fd_out, "=\"", 2);
			write(cmd->fd_out, envpcpy->value, ft_strlen(envpcpy->value));
			write(cmd->fd_out, "\"", 1);
		}
		write(cmd->fd_out, "\n", 1);
		t_env *tmp = envpcpy;
		envpcpy = envpcpy->next;
		free(tmp->var);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
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
    {
		while (cmd->cmd[i])
		{
			var = ft_set_var(cmd->cmd[i]);
			value = ft_set_value(cmd->cmd[i]);
			if (!var)
			{
				printf("not a valide command, use : export [name=value]\n");
				return;
			}
			while (buff->next != NULL)
				buff = buff->next;
			if (buff->next == NULL)
				ft_new_list(var, value, buff);
			i++;
		}
    }
	
}

/*
print export faut trier par ordre alpha
pas gerer export var (sans = valeur)

LES FREE !!!!!!
*/