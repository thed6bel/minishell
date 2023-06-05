/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thed6bel <thed6bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:47:35 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/05 19:51:23 by thed6bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	ft_builtin_pwd(t_mini *n)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	write(n->outfile, cwd, ft_strlen(cwd));
	write(n->outfile, "\n", 1);
	free(cwd);
	g_status = 0;
}
