/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:50:09 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/09 14:15:51 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_execute_single_command(t_mini *cmd, char **envp)
{
	int		status;
	pid_t	pid;

	pid = fork();
	ft_signals_inprocess();
	if (pid == 0)
		ft_child_process(cmd, envp);
	else
		ft_parent_process(cmd, &status, pid);
}

void	ft_pipe_and_execute(t_list *cur, t_prompt *p, int fds[2], int s_stdout)
{
	t_mini	*cmd;

	while (cur)
	{
		cmd = cur->content;
		if (cur->next)
		{
			pipe(fds);
			if (cmd->outfile == 1)
				cmd->outfile = fds[1];
			((t_mini *)cur->next->content)->infile = fds[0];
		}
		if (!ft_execute_builtin(cmd, p) && g_status != 127)
			ft_execute_single_command(cmd, p->envp);
		if (cur->next)
			close(fds[1]);
		if (cmd->outfile != 1)
			dup2(s_stdout, 1);
		cur = cur->next;
	}
}

void	ft_close_and_restore(int fds[2], int s_stdin, int stdout, t_list *cmds)
{
	if (fds[0] != -1)
		close(fds[0]);
	if (g_status != 127)
	{
		ft_lstclear(&cmds, free_content);
		dup2(s_stdin, 0);
		close(s_stdin);
		dup2(stdout, 1);
		close(stdout);
	}
}

void	ft_execute_p_cmds(t_list *cmds, t_prompt *p, t_list *cur, int fds[2])
{
	int		saved_stdin;
	int		saved_stdout;

	cur = cmds;
	saved_stdin = dup(0);
	saved_stdout = dup(1);
	ft_pipe_and_execute(cur, p, fds, saved_stdout);
	ft_close_and_restore(fds, saved_stdin, saved_stdout, cmds);
}

void	ft_execute_commandes(t_prompt *p)
{
	t_list	*cur;
	int		pipe_fds[2];

	cur = NULL;
	pipe_fds[0] = -1;
	pipe_fds[1] = -1;
	ft_execute_p_cmds(p->cmds, p, cur, pipe_fds);
}
