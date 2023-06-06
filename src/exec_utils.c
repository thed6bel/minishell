/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thed6bel <thed6bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:25:46 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/06 17:13:42 by thed6bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exec_builtin_helper(t_mini *n, t_env *env_list, t_prompt *p)
{
	ft_close_fds(n);
	ft_free(p->envp);
	p->envp = env_list_to_tab(env_list);
	free_env_list(env_list);
}

int	ft_execute_other_builtins(t_mini *n, t_prompt *p, t_env *env_list)
{
	t_list	*tmp;

	tmp = p->cmds;
	if (n->full_cmd && (!ft_strncmp(*n->full_cmd, "export",
				ft_strlen(*n->full_cmd) + 1)))
		ft_builtin_export(n, env_list, p);
	else if (n->full_cmd && (!ft_strncmp(*n->full_cmd, "unset",
				ft_strlen(*n->full_cmd) + 1)))
		ft_builtin_unset(n, &env_list);
	else if (n->full_cmd && (!ft_strncmp(*n->full_cmd, "exit",
				ft_strlen(*n->full_cmd) + 1)) && tmp->next == NULL)
		ft_builtin_exit(n, env_list);
	else
	{
		free_env_list(env_list);
		return (0);
	}
	ft_exec_builtin_helper(n, env_list, p);
	return (1);
}

int	ft_execute_builtin(t_mini *n, t_prompt *p)
{
	t_env	*env_list;

	env_list = get_env_list(p->envp);
	if (n->full_cmd && (!ft_strncmp(*n->full_cmd, "cd",
				ft_strlen(*n->full_cmd) + 1)))
		ft_builtin_cd(n, env_list);
	else if (n->full_cmd && (!ft_strncmp(*n->full_cmd, "echo",
				ft_strlen(*n->full_cmd) + 1)))
		ft_buildin_echo(n);
	else if (n->full_cmd && (!ft_strncmp(*n->full_cmd, "pwd",
				ft_strlen(*n->full_cmd) + 1)))
		ft_builtin_pwd(n);
	else if (n->full_cmd && (!ft_strncmp(*n->full_cmd, "env",
				ft_strlen(*n->full_cmd) + 1)))
		built_env(n, env_list);
	else
		return (ft_execute_other_builtins(n, p, env_list));
	ft_exec_builtin_helper(n, env_list, p);
	return (1);
}

void	ft_child_process(t_mini *cmd, char **envp)
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
	if (cmd->full_path != NULL && cmd->full_cmd != NULL)
		execve(cmd->full_path, cmd->full_cmd, envp);
	exit(0);
}

void	ft_parent_process(t_mini *cmd, int *status, pid_t pid)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status) != 0)
		g_status = WEXITSTATUS(*status);
	close(cmd->outfile);
	close(cmd->infile);
}
