/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:50:09 by hucorrei          #+#    #+#             */
/*   Updated: 2023/05/19 13:47:18 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
typedef struct 		s_data
{
	char			*path;
	char			**cmd;
	int 			fd_in;
	int				fd_out;
	struct s_data	*next;
}					t_data;*/

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

void ft_execute_commandes(t_prompt *p, t_mini *n)
{
    int fd[2];
    pid_t pid;
	t_prompt *p1;
	t_mini *n1;
	
	p1 = p;
	n1 = n;
    while (p1->cmds != NULL)
	{
        if (p1->cmds->next != NULL)
		{
            pipe(fd);
        }

        pid = fork();
        if (pid == 0)
		{  // fils
            if (n1->infile != 0)
                dup2(n1->infile, STDIN_FILENO);
            if (p1->cmds->next != NULL)
                dup2(fd[1], STDOUT_FILENO);
            if (n1->outfile != 1)
                dup2(n1->outfile, STDOUT_FILENO);
            close(fd[0]);
			printf("test exec ----------------------------------------1\n");
			if (n1->full_path)
			{
				if (execve(n1->full_path, n1->full_cmd, p1->envp) == -1)
					ft_exit("execve1");	
			}
			else
				ft_cmd_not_found(n1->full_cmd);
        }
		else
		{ // père
            if (p1->cmds->next != NULL)
			{
				printf("test exec ----------------------------------------2\n");
                close(fd[1]);
                dup2(fd[0], STDIN_FILENO);
            }
            close(fd[0]);
            waitpid(pid, NULL, 0);
        }
        p1->cmds = p1->cmds->next;
		printf("test exec ----------------------------------------3\n");
    }
}