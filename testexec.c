/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:25:22 by hucorrei          #+#    #+#             */
/*   Updated: 2023/04/28 10:31:36 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

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
	int i;

	i = 0;
    if (str == NULL)
        return;
    while (str[i] != NULL)
    {
        free(str[i]);
        i++;
    }
    free(str);
}
void	ft_cmd_not_found(char **cmd)
{
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 21);
	ft_free(cmd);
	exit(127);
}

void print_list(t_data *head)
{
    t_data *current = head;

    while (current != NULL)
    {
        printf("path: %s\n", current->path);
        printf("cmd: ");
        for (int i = 0; current->cmd[i] != NULL; i++)
        {
            printf("%s ", current->cmd[i]);
        }
        printf("\n");
        printf("fd_in: %d\n", current->fd_in);
        printf("fd_out: %d\n", current->fd_out);
        printf("pid: %d\n", current->pid);
        printf("\n");
        current = current->next;
    }
}
static char	**ft_get_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*ft_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*slach;
	int		i;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (ft_strdup(cmd));
	paths = ft_get_paths(envp);
	i = 0;
	while (paths[i])
	{
		slach = ft_strjoin(paths[i], "/");
		path = ft_strjoin(slach, cmd);
		free(slach);
		if (!access(path, F_OK))
		{
			ft_free(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free(paths);
	return (0);
}


void ft_execute_commandes(t_data *list, char **env)
{
    int fd[2];
    pid_t pid;

    while (list != NULL)
	{
        if (list->next != NULL)
		{
            pipe(fd);
        }

        pid = fork();
        if (pid == 0)
		{  // fils
            if (list->fd_in != 0)
                dup2(list->fd_in, STDIN_FILENO);
            if (list->next != NULL)
                dup2(fd[1], STDOUT_FILENO);
            if (list->fd_out != 1)
                dup2(list->fd_out, STDOUT_FILENO);
            close(fd[0]);
			if ((list->path) && ft_path(list->path, env))
			{
				if (execve(ft_path(list->path, env), list->cmd, env) == -1)
					ft_exit("execve1");
			}
			else
				ft_cmd_not_found(list->cmd);
        }
		else
		{ // père
            if (list->next != NULL)
			{
                close(fd[1]);
                dup2(fd[0], STDIN_FILENO);
            }
            close(fd[0]);
            waitpid(pid, NULL, 0);
        }
        list = list->next;
    }
}


int main(int argc, char **argv, char **envp) 
{
	char *first_args[] = {"ls", "-la", NULL};
	char *sec_args[] = {"wc", "-c", NULL};
	char *tird_args[] = {"grep", "4", NULL};
	//char *quad_args[] = {"pwd", NULL};
	t_data cmd_list[3] =
	{
		{"ls", first_args, 0, 1, -1, &cmd_list[1]},
		{"wc", sec_args, 0, 1, -1, &cmd_list[2]},
		{"grep", tird_args, 0, 1, -1, NULL}
		//{"pwd", quad_args, 0, 1, -1, NULL}
	};
	sleep(5);
	ft_execute_commandes(cmd_list, envp);
	char *first_args1[] = {"ls", "-la", NULL};
	char *sec_args2[] = {"wc", "-c", NULL};
	char *tird_args3[] = {"pwd", NULL};
	//char *quad_args[] = {"pwd", NULL};
	t_data cmd_lista[3] =
	{
		{"ls", first_args1, 0, 1, -1, &cmd_lista[1]},
		{"wc", sec_args2, 0, 1, -1, &cmd_lista[2]},
		{"pwd", tird_args3, 0, 1, -1, NULL}
		//{"pwd", quad_args, 0, 1, -1, NULL}
	};
	sleep(5);
	ft_execute_commandes(cmd_lista, envp);
	sleep(5);
	return 0;
}
