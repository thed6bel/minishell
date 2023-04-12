/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:17:19 by hucorrei          #+#    #+#             */
/*   Updated: 2023/04/12 15:19:22 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell	minishell;//Struct global vs variable global accpeter??

void	ft_init_struct(void)
{
	minishell.cmds = NULL;
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
	ft_signals_inprocess();
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
	char	**arg;
	char	*path;

	shellp = "nanoshell ~ ";
	ft_signal();
	while (1)
	{
		ft_signal();
    	free(minishell.cmds);
    	minishell.cmds = readline(shellp);
    	add_history(minishell.cmds);
    	if (minishell.cmds == NULL)
        	break;
    	//ft_parsing
    	arg = ft_split(minishell.cmds, ' ');
		if (arg[0] != NULL)
		{
			if (arg[0] && ft_strnstr(minishell.cmds, "exit", 4))
			{
				system("leaks nanoshell");
				break;
			}
			if (arg[0] && (path = ft_path(arg[0], envp)))
			{
				free(path);
				ft_exec(arg, envp);
			}
		}
		ft_free(arg);
	}
	free(minishell.cmds);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	ft_init_struct();//a voir les variables utile au projet
	ft_launch_shell(envp);
}
