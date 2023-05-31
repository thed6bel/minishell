/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:41:09 by hucorrei          #+#    #+#             */
/*   Updated: 2023/05/31 09:57:12 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_mod_ok(t_mini *n, int *mod)
{
	int	i;

	i = *mod + 1;
	while (n->full_cmd[i] != NULL)
	{
		if (ft_strncmp(n->full_cmd[i], "$?", 2) == 0)
			ft_putnbr_fd(g_status, n->outfile);
		else
			write(n->outfile, n->full_cmd[i], ft_strlen(n->full_cmd[i]));
		i++;
		if (n->full_cmd[i] != NULL)
			write(n->outfile, " ", 1);
	}
}

static void	ft_mod_ko(t_mini *n)
{
	int	i;

	i = 1;
	while (n->full_cmd[i] != NULL)
	{
		if (ft_strncmp(n->full_cmd[i], "$?", 2) == 0)
			ft_putnbr_fd(g_status, n->outfile);
		else
			write(n->outfile, n->full_cmd[i], ft_strlen(n->full_cmd[i]));
		i++;
		if (n->full_cmd[i] != NULL)
			write(n->outfile, " ", 1);
	}
	write(n->outfile, "\n", 1);
}

void	ft_set_mod(int *mod, t_mini *n)
{
	int	i;
	int	j;

	i = 1;
	if (n->full_cmd[i] == NULL)
		return ;
	while (n->full_cmd[i] != NULL)
	{
		j = 1;
		if (n->full_cmd[i][0] == '-' && n->full_cmd[i][j] == 'n')
		{
			while (n->full_cmd[i][j] == 'n')
				j++;
			if (n->full_cmd[i][j] != '\0')
				return ;
			else
				*mod += 1;
		}
		i++;
	}
}

void	ft_buildin_echo(t_mini *n)
{
	int		i;
	int		mod;
	char	*codexit;

	i = 1;
	mod = 0;
	ft_set_mod(&mod, n);
	if (mod != 0 && n->full_cmd[i] != NULL)
		ft_mod_ok(n, &mod);
	else
		ft_mod_ko(n);
	g_status = 0;
}
