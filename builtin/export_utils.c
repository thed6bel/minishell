/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:08:35 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/01 12:56:15 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_export(t_mini *n, t_env *envp)
{
	t_env	*envpcpy;
	t_env	*tmp;
	t_env	*new_env;

	envpcpy = NULL;
	ft_copy_env(envp, &envpcpy, tmp, new_env);
	ft_print_env(n, envpcpy);
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
				ft_export_mod_utils(&finalvalue, current, value1);
			current->value = finalvalue;
			return ;
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

int	ft_var_error_print(char *var, char *value)
{
	write(1, "not a valide command, use : export [name=value]\n", 48);
	if (value)
		free(value);
	return (0);
}

int	ft_var_error(char *var, char *value, int *mod)
{
	int	i;

	if (!var)
		return (ft_var_error_print(var, value));
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
