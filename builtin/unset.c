/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:37:24 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/07 09:34:24 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_free_env_node(t_env *node)
{
	free(node->var);
	free(node->value);
	free(node);
}

static void	ft_remove_var_from_env(char *var_to_remove, t_env **envp)
{
	t_env	*buff;
	t_env	*tmp;
	int		i;

	i = 0;
	buff = *envp;
	tmp = buff;
	while (buff != NULL)
	{
		if (!ft_strncmp(buff->var, var_to_remove,
				(ft_strlen(var_to_remove) + 1)))
		{
			if (i != 0)
				tmp->next = buff->next;
			else
				*envp = buff->next;
			ft_free_env_node(buff);
			break ;
		}
		tmp = buff;
		i++;
		buff = buff->next;
	}
}

void	ft_builtin_unset(t_mini *n, t_env **envp)
{
	int	i;

	i = 1;
	if (n->full_cmd[i])
	{
		while (n->full_cmd[i])
		{
			ft_remove_var_from_env(n->full_cmd[i], envp);
			i++;
		}
	}
	else
	{
		g_status = 1;
		printf("unset: not enough arguments\n");
	}
}
