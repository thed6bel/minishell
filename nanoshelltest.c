/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:17:19 by hucorrei          #+#    #+#             */
/*   Updated: 2023/04/26 14:49:27 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handler(int n)
{
	if (n == SIGINT) 
	{
       	struct termios term;
       	tcgetattr(STDIN_FILENO, &term);
        term.c_lflag &= ~ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_handler_process(int n)
{
	if (n == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
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
t_data	*parse_command(char *command)
{
	t_data	*head = NULL;
	t_data	*tail = NULL;
	char	*token = strtok(command, "|");
	int		fd_in = STDIN_FILENO;

	while (token != NULL)
	{
		// créer une nouvelle structure t_data pour la commande courante
		t_data *new_data = malloc(sizeof(t_data));
		new_data->cmd = malloc(256 * sizeof(char*));
		for (int i = 0; i < 256; i++)
			new_data->cmd[i] = NULL;
		new_data->fd_in = fd_in;
		new_data->fd_out = STDOUT_FILENO;
		new_data->pid = -1;
		new_data->next = NULL;

		// extraire le path et les arguments de la commande courante
		char *arg = strtok(token, " ");
		new_data->path = strdup(arg);
		new_data->cmd[0] = strdup(arg);
		int i = 1;
		while ((arg = strtok(NULL, " ")) != NULL)
			new_data->cmd[i++] = strdup(arg);

		// vérifier s'il y a une redirection d'entrée
		if ((arg = strchr(token, '<')) != NULL)
		{
			arg++; // passer le symbole '<'
			while (*arg == ' ') arg++; // passer les espaces éventuels
			char *infile = strdup(arg);
			infile[strcspn(infile, " \t\n")] = '\0'; // supprimer les espaces et les caractères de saut de ligne
			int fd = open(infile, O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				return NULL;
			}
			new_data->fd_in = fd;
			free(infile);
		}

		// vérifier s'il y a une redirection de sortie
		if ((arg = strchr(token, '>')) != NULL)
		{
			arg++; // passer le symbole '>'
			while (*arg == ' ') arg++; // passer les espaces éventuels
			char *outfile = strdup(arg);
			outfile[strcspn(outfile, " \t\n")] = '\0'; // supprimer les espaces et les caractères de saut de ligne
			int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd < 0)
			{
				perror("open");
				return NULL;
			}
			new_data->fd_out = fd;
			free(outfile);
		}

		// ajouter la nouvelle structure t_data à la liste chainée
		if (head == NULL)
		{
			head = new_data;
			tail = new_data;
		}
		else
		{
			tail->next = new_data;
			tail = new_data;
		}

		// passer à la commande suivante
		token = strtok(NULL, "|");
		fd_in = new_data->fd_out; // le fd_out de la commande courante devient le fd_in de la commande suivante
	}

	return head;
}

void print_list(t_data *head)
{
    printf("=== Liste des commandes ===\n");
    while (head != NULL)
    {
        printf("Commande: %s", head->path);
        for (int i = 0; head->cmd[i] != NULL; i++)
            printf(" %s", head->cmd[i]);
        printf("\n");
        printf("  fd_in: %d\n", head->fd_in);
        printf("  fd_out: %d\n", head->fd_out);
        printf("  pid: %d\n", head->pid);
        printf("\n");
        head = head->next;
    }
}

int ft_launch_shell(char **envp)
{
	t_data	*cmds;//free
	char	*shell_prompt;
	char	*p_cmd;
	char	*path;//free
	
	shell_prompt = "nanoshell ~ ";
	p_cmd = NULL;
	path = NULL;

	ft_signal();
	while (1)
	{
		if (p_cmd != NULL)
			free(p_cmd);
		p_cmd = readline(shell_prompt);
		if (p_cmd == NULL)
			break;//gere le ctrl d pour eviter le segfault
		if (p_cmd[0] != '\0')
		{
			add_history(p_cmd);
			cmds = parse_command(p_cmd);
			if (cmds->next != NULL)
			{
				if (ft_strnstr(p_cmd, "exit", 4))
					break;
				//ft_exec_cmd(cmds, envp);
			}
			print_list(cmds);
		}
		ft_signal();
	}
	free(p_cmd);
	//ft_free(cmds);
	//system("leaks nanoshell");
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	
	ft_launch_shell(envp);
}
