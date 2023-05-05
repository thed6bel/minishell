/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:17:19 by hucorrei          #+#    #+#             */
/*   Updated: 2023/04/25 10:25:09 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell	minishell;//Struct global vs variable global accpeter??

void	ft_init_struct(void)
{
	minishell.cmds = NULL;
	minishell.data_cmd.path = NULL;
	minishell.data_cmd.cmd = NULL;
	minishell.shell_prompt = "nanoshell ~ ";
	minishell.data_cmd.fd_in = 0;
	minishell.data_cmd.fd_out = 1;
}

void	ft_handler(int n)
{
	struct termios term;

	if (n == SIGINT) 
	{
       	tcgetattr(STDIN_FILENO, &term);
        term.c_lflag &= ~ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
		rl_redisplay();
		//system("leaks nanoshell");//test leaks apres un ctrl C
		
	}
}

void	ft_handler_process(int n)
{
	if (n == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
	}
}

void	ft_signal()
{
	signal(SIGINT, ft_handler); //ctrl+c
	signal(SIGQUIT, SIG_IGN);//ctrl+d && ctrl+/

}

void	ft_signals_inprocess(void)
{
	signal(SIGINT, ft_handler_process);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return;
	while (str[i])
	{
		if (str[i] != NULL)
			free(str[i]);
		i++;
	}
	if (str != NULL)
		free(str);
}

void	ft_exit(char *a)
{
	if (errno == 0)
		write(2, "Error\n", 6);
	else
		perror(a);
	exit(EXIT_FAILURE);
}

void	ft_cmd_not_found(char **cmd)
{
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 21);
	ft_free(cmd);
	exit(127);
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
char	**ft_parse_cmds(char *cmd)
{
	char	**cmds;
	int		i;
	int		j;

	cmds = ft_calloc(ft_strlen(cmd) + 1, sizeof(char *));
	if (!cmds)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			cmds[j++] = ft_strdup("|");
			i++;
		}
		else
		{
			int start = i;
			while (cmd[i] && cmd[i] != '|')
				i++;
			cmds[j++] = ft_substr(cmd, start, i - start);
		}
	}
	cmds[j] = NULL;
	return (cmds);
}

void ft_exec_cmd_pipes(char **cmds, char **envp)
{
	int fd[2];
    int prev_fd;
    pid_t pid;
    int i;
    char **args;
    int status;

	i = 0;
	prev_fd = 0;
    while (cmds[i]) 
	{
        if (!ft_strncmp(cmds[i], "|", 1))//ajouter la conditions que cmds i+1 existe en cas de echo |xxx
		{
            if (pipe(fd) == -1)
                ft_exit("pipe");
            args = ft_split(cmds[i - 1], ' ');
            if (!args)
			{
				ft_free(cmds);
                ft_exit("malloc");
			}
            pid = fork();
			ft_signals_inprocess();
            if (pid == -1)
                ft_exit("fork");
            if (pid == 0) 
			{
                if (prev_fd != 0) 
				{
                    if (dup2(prev_fd, STDIN_FILENO) == -1)
                        ft_exit("dup2");
                    close(prev_fd);
                }
                if (dup2(fd[1], STDOUT_FILENO) == -1)
                    ft_exit("dup2");
                close(fd[0]);
                close(fd[1]);
                if ((args[0]) && ft_path(args[0], envp))
                    execve(ft_path(args[0], envp), args, envp);
                else
                    ft_cmd_not_found(args);
            }
            close(fd[1]);
            if (prev_fd != 0)
                close(prev_fd);
            prev_fd = fd[0];
            ft_free(args);
			if (wait(&status) == -1)
				ft_exit("wait");
        }
        i++;
    }
    args = ft_split(cmds[i - 1], ' ');
    if (!args)
	{
		free(cmds);
        ft_exit("malloc");
	}
    pid = fork();
	ft_signals_inprocess();
    if (pid == -1)
        ft_exit("fork");
    if (pid == 0) 
	{
        if (prev_fd != 0) {
            if (dup2(prev_fd, STDIN_FILENO) == -1)
                ft_exit("dup2");
            close(prev_fd);
        }
        if ((args[0]) && ft_path(args[0], envp))
            execve(ft_path(args[0], envp), args, envp);
        else
            ft_cmd_not_found(args);
    }
    if (prev_fd != 0)
        close(prev_fd);
    ft_free(args);
    ft_free(cmds);
	if (wait(&status) == -1)
		ft_exit("wait");
}


int ft_launch_shell(char **envp)
{
	minishell.shell_prompt = "nanoshell ~ ";
	ft_signal();
	while (1)
	{
    	free(minishell.cmds);
    	minishell.cmds = readline(minishell.shell_prompt);
    	add_history(minishell.cmds);
    	if (minishell.cmds == NULL)
        	break;
    	//ft_parsing
    	minishell.data_cmd.cmd = ft_split(minishell.cmds, ' ');
		if (minishell.data_cmd.cmd[0] != NULL)
		{
			if (minishell.data_cmd.cmd[0] && ft_strnstr(minishell.cmds, "exit", 4))
			{
				//system("leaks nanoshell");
				//exit(0);
				break;
			}
			if (minishell.data_cmd.cmd[0] && (minishell.data_cmd.path = ft_path(minishell.data_cmd.cmd[0], envp)))
			{
				free(minishell.data_cmd.path);
				ft_exec_cmd_pipes(minishell.data_cmd.cmd, envp);
			}
		}
		ft_free(minishell.data_cmd.cmd);
		ft_signal();
	}
	free(minishell.cmds);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	ft_init_struct();//a voir les variables utile au projet
	ft_launch_shell(envp);
}
