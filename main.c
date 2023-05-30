/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:57:15 by marvin            #+#    #+#             */
/*   Updated: 2023/04/24 11:57:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_signal(void)
{
	signal(SIGINT, ft_handler); //ctrl+c
	signal(SIGQUIT, SIG_IGN);//ctrl+d && ctrl+/
}

void	ft_signals_inprocess(void)
{
	signal(SIGINT, ft_handler_process);
	signal(SIGQUIT, SIG_IGN);
}

static void	mini_getpid(t_prompt *p)
{
	pid_t	pid;

	pid = fork();
	ft_signals_inprocess();
	if (pid < 0)
	{
		mini_perror(FORKERR, NULL, 1);
		ft_free_matrix(&p->envp);
		exit(1);
	}
	if (!pid)
	{
		ft_free_matrix(&p->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	p->pid = pid - 1;
}

static t_prompt	init_vars(t_prompt prompt, char *str, char **argv)
{
	char	*num;

	str = getcwd(NULL, 0);
	prompt.envp = mini_setenv("PWD", str, prompt.envp, 3);
	free(str);
	str = mini_getenv("SHLVL", prompt.envp, 5);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	prompt.envp = mini_setenv("SHLVL", num, prompt.envp, 5);
	free(num);
	str = mini_getenv("PATH", prompt.envp, 4);
	if (!str)
		prompt.envp = mini_setenv("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp, 4);
	free(str);
	str = mini_getenv("_", prompt.envp, 1);
	if (!str)
		prompt.envp = mini_setenv("_", argv[0], prompt.envp, 1);
	free(str);
	return (prompt);
}

static t_prompt	init_prompt(char **argv, char **envp)
{
	t_prompt	prompt;
	char		*str;

	str = NULL;
	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp);
	g_status = 0;
	mini_getpid(&prompt);
	prompt = init_vars(prompt, str, argv);
	return (prompt);
}

t_env	*get_env_list(char **envp)
{
    t_env	*head;
    t_env	*tail;
    t_env	*new_entry;
    char	*equal_pos;
    int		i;
    int		var_len;

    head = NULL;
    tail = NULL;
    i = 0;
    while (envp[i] != NULL)
    {
        equal_pos = ft_strchr(envp[i], '=');
        if (equal_pos != NULL)
        {
            new_entry = (t_env *)malloc(sizeof(t_env));
            if (new_entry == NULL)
                return (NULL);
            var_len = equal_pos - envp[i];
            new_entry->var = ft_substr(envp[i], 0, var_len);
            new_entry->equal = '=';
            new_entry->value = ft_strdup(equal_pos + 1);
            if (new_entry->var == NULL || new_entry->value == NULL)
            {
                free(new_entry->var);
                free(new_entry->value);
                free(new_entry);
                return (NULL);
            }
            new_entry->next = NULL;
            if (tail == NULL)
            {
                head = new_entry;
                tail = new_entry;
            }
            else
            {
                tail->next = new_entry;
                tail = new_entry;
            }
        }
        i++;
    }
    return (head);
}

char **env_list_to_tab(t_env *envp)
{
	int count;
	int len;
	char **env;
	t_env *current;
	int i;

	count = 0;
	current = envp;
	while (current)
	{
		count++;
		current = current->next;
	}
	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	current = envp;
	i = 0;
	while (current)
	{
		len = ft_strlen(current->var) + 1 + ft_strlen(current->value) + 1;
		env[i] = malloc(sizeof(char) * len);
		if (!env[i])
			return (NULL);

		ft_strlcpy(env[i], current->var, len);
		env[i][ft_strlen(current->var)] = '=';
		ft_strlcpy(env[i] + ft_strlen(current->var) + 1, current->value, len - ft_strlen(current->var) - 1);

		current = current->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char				*str;
	char				*out;
	t_prompt			prompt;

	prompt = init_prompt(argv, envp);
	ft_signal();
	while (argv && argc)
	{
		if (out != NULL)
			free(out);
		str = ft_getprompt(prompt);
		if (str)
			out = readline(str);
		else
			out = readline("guest@minishell $ ");
		if (out == NULL)
			break;
		//add_history(out);
		if (!ft_check_args(out, &prompt))
			break ;
		if (str)
			free(str);
		ft_signal();
	}
	free(out);
	exit(g_status);
}
