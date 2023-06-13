/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:13:14 by lowathar          #+#    #+#             */
/*   Updated: 2023/06/13 11:33:25 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_mini	*mini_init(void)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->full_cmd = NULL;
	mini->full_path = "0";
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	return (mini);
}

static t_list	*stop_fill(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, free_content);
	ft_free_matrix(&temp);
	ft_free_matrix(&args);
	return (NULL);
}

static	char	**be_trimmed(char **args)
{
	char	**temp;
	char	*aux;
	int		j;

	j = 0;
	temp = ft_dup_matrix(args);
	while (temp && temp[j])
	{
		aux = ft_strtrim_all(temp[j], 0, 0);
		free(temp[j]);
		temp[j] = aux;
		j++;
	}
	return (temp);
}

static t_mini	*get_params(t_mini *node, char **a[2], int *i)
{
	if (a[0][*i])
	{
		if (ft_check_error(a, i) == -1)
			return (node);
		else if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
			node = get_outfile_double(node, a[1], i);
		else if (a[0][*i][0] == '>')
			node = get_outfile_single(node, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && \
			a[0][*i + 1][0] == '<')
			node = get_infile_double(node, a[1], i);
		else if (a[0][*i][0] == '<')
			node = get_infile_single(node, a[1], i);
		else if (a[0][*i][0] != '|')
			node->full_cmd = ft_extend_matrix(node->full_cmd, a[1][*i]);
		else
		{
			mini_perror(PIPENDERR, NULL, 2);
			*i = -2;
		}
		g_status = 0;
		return (node);
	}
	mini_perror(PIPENDERR, NULL, 2);
	*i = -2;
	return (node);
}

t_list	*fill_node(char **args, int i)
{
	t_list	*cmds[2];
	char	**tmp[2];

	cmds[0] = NULL;
	tmp[1] = be_trimmed(args);
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(mini_init()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		tmp[0] = args;
		cmds[1]->content = get_params(cmds[1]->content, tmp, &i);
		if (i < 0)
			return (stop_fill(cmds[0], args, tmp[1]));
		if (!args[i])
			break ;
	}
	ft_free_matrix(&tmp[1]);
	ft_free_matrix(&args);
	return (cmds[0]);
}
