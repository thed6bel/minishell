/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:44:14 by thed6bel          #+#    #+#             */
/*   Updated: 2023/05/31 10:50:59 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_variable(t_env *buff, char *var, char *value, int *mod)
{
	t_env	*current;

	current = buff;
	while (current != NULL)
	{
		if (!ft_strncmp(current->var, var, ft_strlen(var) + 1))
		{
			free(current->value);
			current->value = value;
			break ;
		}
		current = current->next;
	}
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
			return (NULL);
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

void	check_arg(t_mini *n, t_env *buff, int *mod)
{
	char	*var;
	char	*value;
	int		i;

	while (n->full_cmd[i])
	{
		var = ft_set_var(n->full_cmd[i], mod);
		value = ft_set_value(n->full_cmd[i]);
		if (!ft_var_error(var, value, mod))
			break ;
		if (*mod == 1)
			ft_export_mod(var, value, buff, mod);
		else
			ft_check_variable(buff, var, value, mod);
		i++;
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
	if (n->full_cmd[i] == NULL)
		ft_print_export(n, envp);
	else
		check_arg(n, buff, &mod);
	if (mod == 1)
	{
		free(var);
		free(value);
	}
	if (mod == 2)
		free(var);
}
