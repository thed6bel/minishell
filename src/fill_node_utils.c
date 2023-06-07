/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:43:58 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/07 12:42:12 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_error(char **a[2], int *i)
{
	if ((a[0][0] != NULL && a[0][0][0] == '|') || \
	(a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '|') || \
	((a[0][*i][0] == '>' && a[0][*i + 2]) && (a[0][*i + 2][0] == '|' )))
	{
		mini_perror(PIPENDERR, NULL, 258);
		*i = -2;
		return (-1);
	}
	else if ((a[0][*i][0] == '>' && a[0][*i + 2]) && (a[0][*i + 2][0] == '>'))
	{
		g_status = 258;
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
		*i = -2;
		return (-1);
	}
	else if (((a[0][*i][0] == '>') && (((a[0][*i + 1]) && (a[0][*i + 1][0] \
	== '<')) || ((a[0][*i + 2]) && (a[0][*i + 2][0] == '<')))))
	{
		g_status = 258;
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
		*i = -2;
		return (-1);
	}
	else
		return (0);
}
