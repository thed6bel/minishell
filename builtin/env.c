/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thed6bel <thed6bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:41:04 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/05 19:51:08 by thed6bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	built_env(t_mini *n, t_env *envp)
{
	t_env	*buff;

	buff = envp;
	while (buff != NULL)
	{
		write(n->outfile, buff->var, ft_strlen(buff->var));
		write(n->outfile, "=", 1);
		write(n->outfile, buff->value, ft_strlen(buff->value));
		write(n->outfile, "\n", 1);
		buff = buff->next;
	}
	if (envp != NULL)
		g_status = 0;
}
