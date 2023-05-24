/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:59:09 by lowathar          #+#    #+#             */
/*   Updated: 2023/05/24 14:31:10 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_cmd(char **env_path, char *cmd, char *full_path)
{
	char	*temp;
	int		i;

	i = -1;
	full_path = NULL;
	while (env_path && env_path[++i])
	{
		free(full_path);
		temp = ft_strjoin(env_path[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

static	void	get_cmd(t_prompt *prompt, t_list *cmd, char **s, char *path)
{
	t_mini	*n;

	n = cmd->content;
	path = mini_getenv("PATH", prompt->envp, 4);
	printf("%s\n", path);
	s = ft_split(path, ':');
	free(path);
	n->full_path = find_cmd(s, *n->full_cmd, n->full_path);
	if (!n->full_path || !n->full_cmd[0] || !n->full_cmd[0][0])
	{
		mini_perror(NCMD, *n->full_cmd, 127);
		n->full_path = "0";
	}
}


int builtin(t_prompt *prompt, t_list *cmd, int i)
{
    t_mini  *n;
	t_env 				*env_list;

	while (cmd)
	{
    	n = cmd->content;
		if (!is_builtin(n))
			get_cmd(prompt, cmd, NULL, NULL);
		cmd = cmd->next;
	}
	return (g_status);
}

int	is_builtin(t_mini *n)
{
	int		l;

	//printf("coucou\n");
	if (!n->full_cmd)
		return (0);
	l = ft_strlen(*n->full_cmd);
	if (!ft_strncmp(*n->full_cmd, "pwd", l) && l == 3)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "env", l) && l == 3)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "cd", l) && l == 2)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "export", l) && l == 6)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "unset", l) && l == 5)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "echo", l) && l == 4)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "exit", l) && l == 4)
		return (1);
	return (0);
}

int	ft_dispatch_builtin(t_mini *n, t_prompt *p)
{
	int		l;
	t_env	*env_list;

	l = ft_strlen(*n->full_cmd);
	if (!ft_strncmp(*n->full_cmd, "pwd", l) && l == 3)
		ft_builtin_pwd(n);
	if (!ft_strncmp(*n->full_cmd, "env", l) && l == 3)
	{
		env_list = get_env_list(p->envp);
		built_env(n, env_list);
		ft_free(p->envp);
		p->envp = env_list_to_tab(env_list);
	}
	if (!ft_strncmp(*n->full_cmd, "cd", l) && l == 2)
	{
		env_list = get_env_list(p->envp);
		ft_builtin_cd(n, env_list);
		ft_free(p->envp);
		p->envp = env_list_to_tab(env_list);
	}
	if (!ft_strncmp(*n->full_cmd, "export", l) && l == 6)
	{
		env_list = get_env_list(p->envp);
		ft_builtin_export(n, env_list);
		ft_free(p->envp);
		p->envp = env_list_to_tab(env_list);
	}
	if (!ft_strncmp(*n->full_cmd, "unset", l) && l == 5)
	{
		env_list = get_env_list(p->envp);
		ft_builtin_unset(n, &env_list);
		ft_free(p->envp);
		p->envp = env_list_to_tab(env_list);
	}
	if (!ft_strncmp(*n->full_cmd, "echo", l) && l == 4)
		ft_buildin_echo(n);
	if (!ft_strncmp(*n->full_cmd, "exit", l) && l == 4)
		ft_builtin_exit(n);
	return (0);
}
