/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:44:14 by thed6bel          #+#    #+#             */
/*   Updated: 2023/05/23 11:37:54 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export_mod(char *varfind, char *value1, t_env *buff, int *mod)
{
	char	*finalvalue;
	t_env	*current;
	t_env	*prev;

	current = buff;
	prev = NULL;
	finalvalue = value1;
	while (current != NULL)
	{
		if (!ft_strncmp(current->var, varfind, (ft_strlen(varfind) + 1)))
		{
			if (current->value != NULL)
			{
				finalvalue = ft_strjoin(current->value, value1);
				if (finalvalue == NULL)
				{
					write(1, "Allocation failed\n", 18);
					return;
				}
				free(current->value);
			}
			current->value = finalvalue;
			return;
		}
		prev = current;
		current = current->next;
	}
	*mod = 0;
	if (prev != NULL) 
		ft_new_list(varfind, value1, prev);
	else
		write(1, "Erreur : empty list\n", 20);
}


char	*ft_set_var(char *arg, int *mod)
{
	int		i;
	int		size;
	char	*res;

	i = -1;
	size = 0;
	while (arg[size] && arg[size] != '=' && arg[size] != '+')
		size++;
	if (!arg[size])
		return (arg);
	else if (arg[size] == '+')
	{
		if (arg[size + 1] != '=')
			return NULL;
		*mod = 1;
	}
	if (size == 0)
		return (NULL);
	res = malloc(sizeof(char) * size + 1);
	if (!res)
		return (NULL);
	while (++i < size)
		res[i] = arg[i];
	res[i] = '\0';
	return (res);
}

char	*ft_set_value(char *arg)
{
	int		i;
	int		size;
	char	*res;
	char	*tmp;

	i = -1;
	size = 0;
	tmp = arg;
	while (*tmp && *tmp != '=')
		tmp++;
	if (*tmp == '=')
		tmp++;
	else
		return (NULL);
	while (tmp[size])
		size++;
	res = malloc(sizeof(char *) * size + 1);
	if (!res)
		return (NULL);
	while (++i < size)
		res[i] = tmp[i];
	res[i] = '\0';
	return (res);
}

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

void	ft_print_env(t_mini *n, t_env *envpcpy)
{
	t_env	*tmp;

	ft_sort_list(envpcpy);
	while (envpcpy)
	{
		if (ft_strncmp(envpcpy->var, "_\0", 2) != 0)
		{
			write(n->outfile, "declare -x ", 11);
			write(n->outfile, envpcpy->var, ft_strlen(envpcpy->var));
			if (envpcpy->value)
			{
				write(n->outfile, "=\"", 2);
				write(n->outfile, envpcpy->value, ft_strlen(envpcpy->value));
				write(n->outfile, "\"", 1);
			}
			write(n->outfile, "\n", 1);
		}
		tmp = envpcpy;
		envpcpy = envpcpy->next;
		free(tmp->var);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	ft_print_export(t_mini *n, t_env *envp)
{
	t_env	*envpcpy;
	t_env	*tmp;
	t_env	*new_env;

	envpcpy = NULL;
	ft_copy_env(envp, &envpcpy, tmp, new_env);
	ft_print_env(n, envpcpy);
}

int	ft_var_error(char *var, char *value, int *mod)
{
	int i;

	i = 0;
	while (var[i] != '\0')
	{
		if (i == 0 && !ft_isalpha(var[i]) && var[i] != '_')
		{
			*mod = 1;
			return (0);
		}
		else if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			*mod = 1;
			return (0);
		}
		i++;
	}
	if (!value)
	{
		printf("export: `%s=%s': not a valid identifier\n", var, value);
		return (0);
	}
	return (1);
}


void	ft_check_variable(t_env *buff, char *var, char *value, int *mod)
{
	// Vérifier si la variable est déjà dans la liste chaînée
	t_env *current = buff;
	while (current != NULL)
	{
		if (!ft_strncmp(current->var, var, ft_strlen(var) + 1))
		{
			free(current->value);
			current->value = value;
			break;
		}
		current = current->next;
	}
	// Si la variable n'est pas dans la liste chaînée, l'ajouter
	*mod = 2;
	if (current == NULL)
	{
		*mod = 0;
		while (buff->next != NULL)
			buff = buff->next;
		if (buff->next == NULL)
			ft_new_list(var, value, buff);
	}
}

void	ft_builtin_export(t_mini *n, t_env *envp)
{
	t_env	*buff;
	char	*var;
	char	*value;
	int		i;
	int		mod;

	buff = envp;
	i = 1;
	mod = 0;
	//protec NULL return??
	if (n->full_cmd[i] == NULL)
		ft_print_export(n, envp);
	else
	{
		while (n->full_cmd[i])
		{
			var = ft_set_var(n->full_cmd[i], &mod);
			value = ft_set_value(n->full_cmd[i]);
			if (!ft_var_error(var, value, &mod))
				break;
			if (mod == 1)
				ft_export_mod(var, value, buff, &mod);
			else
                ft_check_variable(buff, var, value, &mod);
			i++;
		}
	}
	if (mod == 1)//si +=
	{
		free(var);
		free(value);
	}
	if (mod == 2)//si la variable existe
	{
		free(var);
		//free(value);
	}
}

