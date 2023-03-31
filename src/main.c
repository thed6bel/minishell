/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:17:19 by hucorrei          #+#    #+#             */
/*   Updated: 2023/03/31 09:20:52 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_exec(char **arg, char **envp)
{
	pid_t pid;
	pid_t wpid;

	pid = fork();
	if (pid == 0)
	{
		printf("test exec\n");
		//execve(ft_path(arg[0], envp), arg, envp);
	}
	return (1);
}

int ft_launch_shell(char **envp)
{
	char	*shellp;
	char	*cmd;
	char	**arg;
	int stat;

	stat = 1;
	shellp = "minishell: ";
	//printf("%s\n", cmd);//verif de readline
	while (cmd != NULL)
	{
		add_history(cmd);
		cmd = readline(shellp);
		arg = ft_split(cmd, ' ');
		shellp = "minishell: ";

		//ft_exec(arg, envp);
	}
	free(cmd);//free du malloc de readline
	free(arg);//free split
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	ft_launch_shell(envp);
	return (EXIT_SUCCESS);
}