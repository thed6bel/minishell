/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:37:24 by hucorrei          #+#    #+#             */
/*   Updated: 2023/05/31 10:06:03 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_env_node(t_env *node)
{
	free(node->var);
	free(node->value);
	free(node);
}

void	ft_builtin_unset(t_mini *n, t_env **envp)
{
	t_env	*buff;
	t_env	*tmp;
	int		i;

	i = 0;
	buff = *envp;
	tmp = buff;
	while (buff != NULL)
	{
		if (!ft_strncmp(buff->var, n->full_cmd[1],
				(ft_strlen(n->full_cmd[1]) + 1)))
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
