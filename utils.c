/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:53:11 by lowathar          #+#    #+#             */
/*   Updated: 2023/05/30 15:12:54 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchars_i(const char *s, char *set)
{
	int				i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (ft_strchr(set, s[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strchr_i(const char *s, int c)
{
	unsigned char	c_unsigned;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	c_unsigned = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c_unsigned)
			return (i);
		i++;
	}
	if (c_unsigned == '\0')
		return (i);
	return (-1);
}

void	free_content(void *content)
{
	t_mini	*node;

	node = content;
	ft_free_matrix(&node->full_cmd);
	if (ft_strncmp(node->full_path, "0", 1))
		free(node->full_path);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
	free(node);
}

void	print_cmds(t_prompt *prompt)
{
	t_list	*cmds;
	t_mini	*cmd;
	int		i;
	int		j;

	i = 1;
	*cmds = *prompt->cmds;
	while (cmds != NULL)
	{
		printf("===================\n");
		printf("Node numero : %i\n", i);
		i++;
		cmd = cmds->content;
		j = 0;
		while (j < 5 && cmd->full_cmd[j] != NULL)
		{
			printf("Full command: %s\n", cmd->full_cmd[j]);
			j++;
		}
		printf("Full path: %s\n", cmd->full_path);
		printf("Input file descriptor: %d\n", cmd->infile);
		printf("Output file descriptor: %d\n", cmd->outfile);
		cmds = cmds->next;
	}
}
