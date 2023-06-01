/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:14:07 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/01 10:15:52 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_env_tab(char **env, t_env *current, int i)
{
	int	len;

	len = ft_strlen(current->var) + 1 + ft_strlen(current->value) + 1;
	env[i] = malloc(sizeof(char) * len);
	if (!env[i])
		return ;
	ft_strlcpy(env[i], current->var, len);
	env[i][ft_strlen(current->var)] = '=';
	ft_strlcpy(env[i] + ft_strlen(current->var) + 1, current->value,
		len - ft_strlen(current->var) - 1);
}

void	add_env_entry(t_env **head, t_env **tail, t_env *new_entry)
{
	if (*tail == NULL)
	{
		*head = new_entry;
		*tail = new_entry;
	}
	else
	{
		(*tail)->next = new_entry;
		*tail = new_entry;
	}
}
