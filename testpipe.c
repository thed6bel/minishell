#include "../minishell.h"

char **parse_cmd(char *cmd)
{
    char **cmds = NULL;
    char *token;
    int i = 0;
    const char *sep = "|";
    token = strtok(cmd, sep);
    while (token != NULL)
    {
        cmds = realloc(cmds, (i + 1) * sizeof(char *));
        cmds[i] = malloc((strlen(token) + 1) * sizeof(char));
        strcpy(cmds[i], token);
        i++;
        token = strtok(NULL, sep);
        if (token != NULL)
        {
            cmds = realloc(cmds, (i + 1) * sizeof(char *));
            cmds[i] = malloc(2 * sizeof(char));
            strcpy(cmds[i], "|");
            i++;
        }
    }
    cmds = realloc(cmds, (i + 1) * sizeof(char *));
    cmds[i] = NULL;
    return cmds;
}

int execute_cmds(char **cmds, char **envp)
{
    int i = 0;
    int prev_pipe[2] = {0, 0};
    int next_pipe[2] = {0, 0};
    char **args;
    char *command;
    pid_t pid;
    int status;

    while (cmds[i] != NULL)
    {
        if (pipe(next_pipe) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            if (i != 0)
            {
                dup2(prev_pipe[0], STDIN_FILENO);
                close(prev_pipe[0]);
                close(prev_pipe[1]);
            }

            if (cmds[i + 1] != NULL)
            {
                dup2(next_pipe[1], STDOUT_FILENO);
                close(next_pipe[0]);
                close(next_pipe[1]);
            }

            command = ft_path(cmds[i], envp);
            if (command == NULL)
            {
                fprintf(stderr, "execute_cmds: command not found: %s\n", cmds[i]);
                exit(EXIT_FAILURE);
            }

            args = parse_cmd(cmds[i]);
            execve(command, args, envp);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(pid, &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            {
                fprintf(stderr, "execute_cmds: command failed: %s\n", cmds[i]);
                return -1;
            }

            if (prev_pipe[0] != 0) close(prev_pipe[0]);
            if (prev_pipe[1] != 0) close(prev_pipe[1]);
            prev_pipe[0] = next_pipe[0];
            prev_pipe[1] = next_pipe[1];
        }

        i++;
    }

    return 0;
}

void	ft_exec_pipe(char **cmds, char **envp)
{
	int num_cmds = 0;
	while (cmds[num_cmds] != NULL)
		num_cmds++;

	int pipefds[2];
	int prev_pipefd = -1;
	int i = 0;

	while (i < num_cmds)
	{
		if (strcmp(cmds[i], "|") == 0)
		{
			// create a pipe
			if (pipe(pipefds) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}

			// fork a child process
			pid_t pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}

			if (pid == 0)
			{
				// child process
				close(pipefds[0]); // close the read end of the pipe

				// set the write end of the pipe to stdout
				if (dup2(pipefds[1], STDOUT_FILENO) == -1)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}

				// execute the previous command
				char **prev_cmd = cmds + prev_pipefd + 1;

				char *path = ft_path(prev_cmd[0], envp);
				if (!path)
				{
					fprintf(stderr, "%s: command not found\n", prev_cmd[0]);
					exit(EXIT_FAILURE);
				}

				if (execve(path, prev_cmd, envp) == -1)
				{
					perror(path);
					exit(EXIT_FAILURE);
				}
			}

			// parent process
			close(pipefds[1]); // close the write end of the pipe

			// save the read end of the pipe for the next command
			prev_pipefd = i;
		}

		i++;
	}

	// execute the last command
	char **last_cmd = cmds + prev_pipefd + 1;

	char *path = ft_path(last_cmd[0], envp);
	if (!path)
	{
		fprintf(stderr, "%s: command not found\n", last_cmd[0]);
		exit(EXIT_FAILURE);
	}

	if (execve(path, last_cmd, envp) == -1)
	{
		perror(path);
		exit(EXIT_FAILURE);
	}
}

int ft_exec_cmd_pipes(char **cmds, char **envp)
{
    int i;
    int fd[2];
    pid_t pid;
    char *path;
    char **cmd;

    if (!cmds || !envp)
        return (0);
    i = 0;
    while (cmds[i])
    {
        if (!ft_strncmp(cmds[i], "|", 50))
        {
            if (pipe(fd) == -1)
            {
				printf("1\n");
                perror("pipe");
                return (1);
            }
            pid = fork();
            if (pid == -1)
            {
				printf("2\n");
                perror("fork");
                return (pid);
            }
            if (pid == 0)
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
                cmd = ft_split(cmds[i - 1], ' ');
                path = ft_path(cmd[0], envp);
                if (!path)
                {
                    fprintf(stderr, "command not found: %s\n", cmd[0]);
                    ft_free(cmd);
                    exit(EXIT_FAILURE);
                }
                if (execve(path, cmd, envp) == -1)
                {
                    perror("execve");
                    ft_free(cmd);
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                close(fd[1]);
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
            }
        }
        i++;
    }
    cmd = ft_split(cmds[i - 1], ' ');
    path = ft_path(cmd[0], envp);
    if (!path)
    {
		printf("3\n");
        fprintf(stderr, "command not found: %s\n", cmd[0]);
        ft_free(cmd);
        return (pid);
    }
    if (execve(path, cmd, envp) == -1)
    {
		printf("4\n");
        perror("execve");
        ft_free(cmd);
        return (pid);
    }
	printf("5\n");
    return (pid);
}

