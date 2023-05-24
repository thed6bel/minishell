/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:50:09 by hucorrei          #+#    #+#             */
/*   Updated: 2023/05/23 14:31:16 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char *a)
{
	if (errno == 0)
		write(2, "Error\n", 6);
	else
		perror(a);
	exit(EXIT_FAILURE);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
void	ft_execute_commandes(t_prompt *p)
{
	int			fd[2];
	pid_t		pid;
	t_prompt	*p1;
	t_mini		*n1;
	int			in;

	in = 0;
	p1 = p;
	n1 = p->cmds->content;
	while (p1->cmds != NULL)
	{
		if (pipe(fd) == -1)
			ft_exit("pipe error:");
		pid = fork();
		if (pid == -1)
			ft_exit("fork error:");
		else if (pid == 0)
		{
			if (n1->infile != 0)
			{
				dup2(n1->infile, STDIN_FILENO);
				close(n1->infile);
			}
			if (n1->outfile != 1)
			{
				dup2(n1->outfile, STDOUT_FILENO);
				close(n1->outfile);
			}
			dup2(in, STDIN_FILENO);
			if (in != 0)
				close(in);
			if (p1->cmds->next != NULL)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			close(fd[0]);
			if (is_builtin(n1))
				ft_dispatch_builtin(n1, p);
			else
				execve(n1->full_path, n1->full_cmd, p1->envp);
			exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(fd[1]);
			if (in != 0)
				close(in);
			in = fd[0];
			if (n1->infile != 0)
				close(n1->infile);
			if (n1->outfile != 1)
				close(n1->outfile);
		}
		p1->cmds = p1->cmds->next;
		if (p1->cmds != NULL)
			n1 = p1->cmds->content;
	}
	close(in);
}
