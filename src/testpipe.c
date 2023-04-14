#include "../minishell.h"

t_shell	minishell;

void	ft_exec2(char **cmd, char **envp)
{
	printf("ft exec2, %s\n", cmd[0]);
	execve(ft_path(cmd[0], envp), cmd, envp);
}

void ft_child_cmd_one(int fd_in, int pipe_fd[], char **cmd, char **envp)
{
	printf("ft child\n");
	if (minishell.data_cmd.fd_in == 0)
		dup2(fd_in, 0);
	else
		dup2(minishell.data_cmd.fd_in, 0);
	if (cmd + 1 != NULL && minishell.data_cmd.fd_out == 1)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
	}
	else
	{
		dup2(minishell.data_cmd.fd_out, 1);
		close(pipe_fd[1]);
	}
	close(pipe_fd[0]);
	ft_exec(cmd, envp);
}

void ft_cmd_exec(char **cmd, char **envp)
{
	int	pipe_fd[2];
	int fd_in;
	int ret;
	int i;
	int status;

	i = 0;
	ret = 0;
	fd_in = 0;
	while (cmd != NULL)
	{
		pipe(pipe_fd);
		minishell.pid = fork();
		if (minishell.pid == -1)
			exit(0);
		else if (minishell.pid == 0)
		{
			printf("after fork if pid =0\n");
			ft_child_cmd_one(fd_in, pipe_fd, cmd, envp);
		}
		close (pipe_fd[1]);
		if (fd_in != 0)
			close(fd_in);
		fd_in = pipe_fd[0];
		cmd++;// voir si ont utilise des liste => cdm = cdm->next
	}
	if (fd_in != 0)
		close(fd_in);
	while (ret != -1)
		ret = wait(&status);
}