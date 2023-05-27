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
	{
		perror(a);
		g_status = 127;
	}
	exit(g_status);
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

int ft_execute_builtin_cd(t_mini *n, t_prompt *p)
{
	int l = ft_strlen(*n->full_cmd);
	if (!ft_strncmp(*n->full_cmd, "cd", l) && l == 2)
	{
		t_env *env_list = get_env_list(p->envp);
		ft_builtin_cd(n, env_list);
		pid_t pid = fork();
		if (pid == 0)
			exit(0);
		else
			waitpid(pid, NULL, 0); 
		ft_free(p->envp);
		p->envp = env_list_to_tab(env_list);
		return (1);
	}
	return (0);
}

int ft_execute_builtin_echo(t_mini *n)
{
	int l = ft_strlen(*n->full_cmd);
	if (!ft_strncmp(*n->full_cmd, "echo", l) && l == 4)
	{
		ft_buildin_echo(n);
		return (1);
	}
	return (0);
}

int ft_execute_builtin_pwd(t_mini *n)
{
	int l = ft_strlen(*n->full_cmd);
	if (!ft_strncmp(*n->full_cmd, "pwd", l) && l == 3)
	{
		ft_builtin_pwd(n);
		return (1);
	}
	return (0);
}

int ft_execute_builtin_env(t_mini *n, t_prompt *p)
{
	int l = ft_strlen(*n->full_cmd);
	if (!ft_strncmp(*n->full_cmd, "env", l) && l == 3)
	{
		t_env *env_list = get_env_list(p->envp);
		built_env(n, env_list);
		pid_t pid = fork();
		if (pid == 0)
			exit(0);
		else
			waitpid(pid, NULL, 0); 
		ft_free(p->envp);
		p->envp = env_list_to_tab(env_list);
		return (1);
	}
	return (0);
}

int ft_execute_builtin_export(t_mini *n, t_prompt *p)
{
	int l = ft_strlen(*n->full_cmd);
	if (!ft_strncmp(*n->full_cmd, "export", l) && l == 6)
	{
		t_env *env_list = get_env_list(p->envp);
		ft_builtin_export(n, env_list);
		pid_t pid = fork();
		if (pid == 0)
			exit(0);
		else
			waitpid(pid, NULL, 0); 
		ft_free(p->envp);
		p->envp = env_list_to_tab(env_list);
		return (1);
	}
	return (0);
}

int ft_execute_builtin_unset(t_mini *n, t_prompt *p)
{
	int l = ft_strlen(*n->full_cmd);
	if (!ft_strncmp(*n->full_cmd, "unset", l) && l == 5)
	{
		t_env *env_list = get_env_list(p->envp);
		ft_builtin_unset(n, &env_list);
		pid_t pid = fork();
		if (pid == 0)
			exit(0);
		else
			waitpid(pid, NULL, 0); 
		ft_free(p->envp);
		p->envp = env_list_to_tab(env_list);
		return (1);
	}
	return (0);
}

int ft_execute_builtin_exit(t_mini *n)
{
	int l = ft_strlen(*n->full_cmd);
	if (!ft_strncmp(*n->full_cmd, "exit", l) && l == 4)
	{
		ft_builtin_exit(n);
		return (1);
	}
	return (0);
}

int ft_execute_builtin(t_mini *n, t_prompt *p, int i)
{
	int		l;
	t_env	*env_list;
	pid_t	pid;

	if (i == 1)
		return (1);
	l = ft_strlen(*n->full_cmd);
	if (ft_execute_builtin_cd(n, p))
		return (1);
	else if (ft_execute_builtin_echo(n))
		return (1);
	else if (ft_execute_builtin_pwd(n))
		return (1);
	else if (ft_execute_builtin_env(n, p))
		return (1);
	else if (ft_execute_builtin_export(n, p))
		return (1);
	else if (ft_execute_builtin_unset(n, p))
		return (1);
	else if (ft_execute_builtin_exit(n))
		return (1);
	else
		return (0);
}

void ft_configure_io(t_mini *cmd)
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
}

void ft_execute_command(t_mini *cmd, char **envp)
{
	if (cmd->full_path != NULL)
	{
		execve(cmd->full_path, cmd->full_cmd, envp); 
		ft_exit("execve ");
	}
}

void ft_wait_for_child(pid_t pid, t_mini *cmd)
{
	int status;
	waitpid(pid, &status, 0);
	//if (WIFEXITED(status) != 0)
	//g_status = WEXITSTATUS(status);
}

void ft_close_io(t_mini *cmd)
{
	if (cmd->outfile)
		close(cmd->outfile);
	if (cmd->infile)
		close(cmd->infile);
}

void ft_execute_single_command(t_mini *cmd, char **envp)
{
	pid_t pid = fork();
	if (pid == 0)
	{ // Sous-processus
		ft_configure_io(cmd);
		ft_execute_command(cmd, envp);
	}
	else
	{ // Processus parent
		ft_wait_for_child(pid, cmd);
		ft_close_io(cmd);
	}
}

void    ft_execute_piped_commands(t_list *cmds, t_prompt *p)
{
	t_list	*cur;
	t_mini	*cmd;
	int		pipe_fds[2];
	int		saved_stdin;
	int		saved_stdout;
	
	cur = cmds;
	saved_stdin = dup(0);
	saved_stdout = dup(1);
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
		if (cmd->outfile != 1) 
		{  
			if (!ft_execute_builtin(cmd, p, 1))// 1 = on execute pas les builtins  
			{  
				dup2(cmd->outfile, 1);  
				close(cmd->outfile);
			}
		}
		if (!ft_execute_builtin(cmd, p, 0)) // 0 = on execute les builtins
			ft_execute_single_command(cmd, p->envp);
		if (cur->next)
			close(pipe_fds[1]);
		if (cmd->outfile != 1)  
			dup2(saved_stdout, 1);
		cur = cur->next;
	}
	close(pipe_fds[0]);
	dup2(saved_stdin, 0);
	dup2(saved_stdout, 1);
	close(saved_stdin);
	close(saved_stdout);
}

void ft_execute_commandes(t_prompt *p)
{
	ft_execute_piped_commands(p->cmds, p);
}
