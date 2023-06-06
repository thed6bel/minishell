/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:43:58 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/06 11:14:23 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_mini	*ft_get_redir(t_mini *node, char **a[2], int *i)
{
	if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>'
		&& a[0][*i + 2][0] != '|')
	node = get_outfile_double(node, a[1], i);
	else if (a[0][*i][0] == '>' && a[0][*i + 1][0] != '|')
		node = get_outfile_single(node, a[1], i);
	else if (a[0][*i][0] == '<' && a[0][*i + 1] &&
		a[0][*i + 1][0] == '<')
		node = get_infile_double(node, a[1], i);
	else if (a[0][*i][0] == '<')
		node = get_infile_single(node, a[1], i);
	return (node);
}
