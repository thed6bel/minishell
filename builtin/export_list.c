/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:08:32 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/13 11:14:31 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_new_list(char *var, char *value, t_env *buff)
{
	t_env	*tmp;
	t_env	*new;

	if (value)
	{
		tmp = buff;
		new = malloc(sizeof(t_env));
		if (!new)
			return ;
		tmp->next = new;
		new->next = NULL;
		new->var = var;
		new->equal = '=';
		new->value = value;
	}
	else
		write(1, "not a valide command, use : export [VARname=value]\n", 51);
}

void	ft_swap_env(t_env *env1, t_env *env2)
{
	char	*var_tmp;
	char	equal_tmp;
	char	*value_tmp;

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
	int		swap;
	t_env	*tmp;
	t_env	*list;

	list = NULL;
	swap = 1;
	while (swap)
	{
		swap = 0;
		tmp = envpcpy;
		while (tmp->next != list)
		{
			if (ft_strncmp(tmp->var, tmp->next->var,
					ft_strlen(tmp->var) + 1) > 0)
			{
				ft_swap_env(tmp, tmp->next);
				swap = 1;
			}
			tmp = tmp->next;
		}
		list = tmp;
	}
}

void	ft_copy_env(t_env *envp, t_env **envpcpy, t_env	*tmp, t_env	*new_env)
{
	while (envp)
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			return ;
		new_env->var = ft_strdup(envp->var);
		new_env->equal = envp->equal;
		if (envp->value)
			new_env->value = ft_strdup(envp->value);
		else
			new_env->value = NULL;
		new_env->next = NULL;
		if (*envpcpy == NULL)
		{
			*envpcpy = new_env;
			tmp = new_env;
		}
		else
		{
			tmp->next = new_env;
			tmp = tmp->next;
		}
		envp = envp->next;
	}
}

void	ft_export_mod_utils(char **finalvalue, t_env *current, char *value1)
{
	*finalvalue = ft_strjoin(current->value, value1);
	if (*finalvalue == NULL)
	{
		write(1, "Allocation failed\n", 18);
		return ;
	}
	free(current->value);
}