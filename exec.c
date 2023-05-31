/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:50:09 by hucorrei          #+#    #+#             */
/*   Updated: 2023/05/31 11:47:51 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_builtin(t_mini *n, t_prompt *p, int i)
{
	t_env	*env_list;

	if (i == 1)
		return (1);
	env_list = get_env_list(p->envp);
	if (!ft_strncmp(*n->full_cmd, "cd", ft_strlen(*n->full_cmd)))
		ft_builtin_cd(n, env_list);
	else if (!ft_strncmp(*n->full_cmd, "echo", ft_strlen(*n->full_cmd)))
		ft_buildin_echo(n);
	else if (!ft_strncmp(*n->full_cmd, "pwd", ft_strlen(*n->full_cmd)))
		ft_builtin_pwd(n);
	else if (!ft_strncmp(*n->full_cmd, "env", ft_strlen(*n->full_cmd)))
		built_env(n, env_list);
	else if (!ft_strncmp(*n->full_cmd, "export", ft_strlen(*n->full_cmd)))
		ft_builtin_export(n, env_list);
	else if (!ft_strncmp(*n->full_cmd, "unset", ft_strlen(*n->full_cmd)))
		ft_builtin_unset(n, &env_list);
	else if (!ft_strncmp(*n->full_cmd, "exit", ft_strlen(*n->full_cmd)))
		ft_builtin_exit(n, env_list);
	else
	{
		free_env_list(env_list);
		return (0);
	}
	ft_close_fds(n);
	ft_free(p->envp);
	p->envp = env_list_to_tab(env_list);
	free_env_list(env_list);
	return (1);
}

void	ft_execute_single_command(t_mini *cmd, char **envp)
{
	int		status;
	pid_t	pid;

	pid = fork();
	ft_signals_inprocess();
	if (pid == 0)
	{
		if (cmd->infile != 0)
		{
			dup2(cmd->infile, 0);
			close(cmd->infile);
		}
		if (cmd->outfile != 1)
		{
			dup2(cmd->outfile, 1);
			close(cmd->outfile);
		}
		if (cmd->full_path != NULL)
		{
			execve(cmd->full_path, cmd->full_cmd, envp);
			ft_exit("execve ");
		}
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) != 0)
			g_status = WEXITSTATUS(status);
		close(cmd->outfile);
		close(cmd->infile);
	}
}

void	ft_execute_piped_commands(t_list *cmds, t_prompt *p)
{
	t_list	*cur;
	t_mini	*cmd;
	int		pipe_fds[2];
	int		saved_stdin;
	int		saved_stdout;

	cur = cmds;
	saved_stdin = dup(0);
	saved_stdout = dup(1);
	pipe_fds[0] = -1;
	pipe_fds[1] = -1;
	while (cur)
	{
		cmd = cur->content;
		if (cur->next)
		{
			pipe(pipe_fds);
			if (cmd->outfile == 1)
				cmd->outfile = pipe_fds[1];
			((t_mini *)cur->next->content)->infile = pipe_fds[0];
		}
		if (!ft_execute_builtin(cmd, p, 0))
			ft_execute_single_command(cmd, p->envp);
		if (cur->next)
			close(pipe_fds[1]);
		if (cmd->outfile != 1)
			dup2(saved_stdout, 1);
		cur = cur->next;
	}
	if (pipe_fds[0] != -1)
		close(pipe_fds[0]);
	ft_lstclear(&cmds, free_content);
	dup2(saved_stdin, 0);
	close(saved_stdin);
	dup2(saved_stdout, 1);
	close(saved_stdout);
}

void	ft_execute_commandes(t_prompt *p)
{
	ft_execute_piped_commands(p->cmds, p);
}
