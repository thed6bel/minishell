/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:09:56 by lowathar          #+#    #+#             */
/*   Updated: 2023/04/27 15:15:06 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern  int status;

int	get_fd(int oldfd, char *path, int flags[2])
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		return(-1);
        //error(); // error no file in directory
	else if (!flags[0] && access(path, R_OK) == -1)
		return(-1);
        //error(); // permission denied
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		return(-1);
        //error(); // permission denied
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}
t_mini	*get_outfile_double(t_mini *node, char **args, int *i)
{
    char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)])
		node->outfile = get_fd(node->outfile, args[*i], flags);
	// if (!args[*i] || node->outfile == -1)
	// {
	// 	*i = -1;
	// 	if (node->outfile != -1)
	// 	{
	// 		ft_putendl_fd(nl, 2);
	// 		status = 2;
	// 	}
	// 	else
	// 		status = 1;
	// }
	return (node);
}
t_mini	*get_outfile_single(t_mini *node, char **args, int *i)
{
    char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[*i])
		node->outfile = get_fd(node->outfile, args[*i], flags);
	// if (!args[*i] || node->outfile == -1)
	// {
	// 	*i = -1;
	// 	if (node->outfile != -1)
	// 	{
	// 		ft_putendl_fd(nl, 2);
	// 		status = 2;
	// 	}
	// 	else
	// 		status = 1;
	// }
	return (node);
}

t_mini	*get_infile_single(t_mini *node, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[*i])
		node->infile = get_fd(node->infile, args[*i], flags);
	// if (!args[*i] || node->infile == -1)
	// {
	// 	*i = -1;
	// 	if (node->infile != -1)
	// 	{
	// 		ft_putendl_fd(nl, 2);
	// 		status = 2;
	// 	}
	// 	else
	// 		status = 1;
	// }
	return (node);
}

t_mini  *get_infile_double(t_mini *node, char **args, int *i)
{

}