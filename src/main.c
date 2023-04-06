/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:17:19 by hucorrei          #+#    #+#             */
/*   Updated: 2023/04/06 14:19:34 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell	minishell;//Struct global vs variable global accpeter??

void	ft_handler(int n)
{
	int sig_fd;
	struct termios *a;
	struct termios *b;
	struct termios term;
	
	sig_fd = 1;
	a = malloc(sizeof(struct termios));
	b = malloc(sizeof(struct termios));

	if (n == SIGINT) 
	{
        tcgetattr(STDIN_FILENO, &term);
        term.c_lflag &= ~ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
	}
	if (n == SIGQUIT)
	{
		printf("test\n");
	}
}

void	ft_signal()
{
	signal(SIGINT, ft_handler); //ctrl+c
	signal(SIGQUIT, SIG_IGN);//ctrl+d et ctrl+/
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static char	**ft_get_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*ft_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*slach;
	int		i;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
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

int ft_exec(char **arg, char **envp)
{
	pid_t	pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execve(ft_path(arg[0], envp), arg, envp);
	}
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		}
	}
	return (pid);
}

int ft_launch_shell(char **envp)
{
	char	*shellp;
	char	*cmd;
	char	**arg;

	shellp = "nanoshell ~ ";
	//printf("%s\n", cmd);//verif de readline
	cmd = (char *) malloc(sizeof(char) * 1024);
	ft_signal();
	while (1)
	{
		add_history(cmd);
		cmd = readline(shellp);
		arg = ft_split(cmd, ' ');
		//printf("cmd1 : %s\n", arg[0]);
		//printf("arg2 : %s\n", arg[1]);
		if (ft_strnstr(cmd, "exit", 4))
			break;
		ft_exec(arg, envp);
		ft_signal();
	}
	free(cmd);//free du malloc de readline
	free(arg);//free split
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	ft_launch_shell(envp);
}
