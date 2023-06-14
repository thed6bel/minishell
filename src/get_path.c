/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:59:09 by lowathar          #+#    #+#             */
/*   Updated: 2023/06/14 11:10:48 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static void	update_cmd_path(t_list *cmd, char **s)
{
	t_mini	*n;

	n = cmd->content;
	s = ft_split(*n->full_cmd, '/');
	n->full_path = ft_strdup(*n->full_cmd);
	if (s[1])
		n->full_cmd[0] = ft_strdup(&s[1][ft_matrixlen(s)] - 2);
	if (!s[1])
		mini_perror(NDIR, n->full_cmd[0], 127);
	free(n->full_cmd[0]);
}

static void	get_cmd(t_prompt *prompt, t_list *cmd, char **s, char *path)
{
	t_mini	*n;
	DIR		*dir;

	n = cmd->content;
	dir = NULL;
	if (n && n->full_cmd)
		dir = opendir(*n->full_cmd);
	if (n && n->full_cmd && ft_strchr(*n->full_cmd, '/') && !dir)
		update_cmd_path(cmd, s);
	else if (!is_builtin(n) && n && n->full_cmd)
	{
		path = mini_getenv("PATH", prompt->envp, 4);
		s = ft_split(path, ':');
		free(path);
		n->full_path = find_cmd(s, *n->full_cmd, n->full_path);
	}
	ft_free(s);
	if ((!n->full_path || (n->full_cmd && (!n->full_cmd[0]
				|| !n->full_cmd[0][0]))) && !dir)
	{
		//printf("coucou\n");
		mini_perror(NCMD, *n->full_cmd, 127);
		n->full_path = NULL;
	}
	// else if (g_status != 127)
	// 	g_status = 0;
	if (!is_builtin(n) && n && n->full_cmd && dir)
		mini_perror(IS_DIR, *n->full_cmd, 126);
	else if (!is_builtin(n) && n && n->full_path && \
		access(n->full_path, F_OK) == -1)
		mini_perror(NDIR, n->full_path, 127);
	else if (!is_builtin(n) && n && n->full_path && \
		access(n->full_path, X_OK) == -1)
		mini_perror(NPERM, n->full_path, 126);
	if (dir)
		closedir(dir);
	//ft_free_matrix(&s);
}

int	builtin(t_prompt *prompt, t_list *cmd)
{
	t_mini	*n;

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
