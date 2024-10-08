/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:47:32 by lowathar          #+#    #+#             */
/*   Updated: 2023/06/07 10:43:08 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_heredoc(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
	{
		mini_perror(PIPENDERR, NULL, 258);
		return (-1);
	}
	else if (str[i] == '<')
	{
		g_status = 258;
		ft_putstr_fd("minishell: syntax error \
near unexpected token `newline'\n", 2);
		return (-1);
	}
	else if (str[i] == '>')
	{
		g_status = 258;
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
		return (-1);
	}
	else
		return (0);
}

char	*get_here_str(char *str[2], size_t len, char *limit, char *warn)
{
	char	*temp;

	while (g_status != 130 && (!str[0] || ft_strncmp(str[0], limit, len) \
		|| ft_strlen(limit) != len))
	{
		temp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(temp);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", warn, limit);
			break ;
		}
		temp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

int	get_here_doc(char *str[2], char *aux[2])
{
	int		fd[2];

	g_status = 0;
	if (ft_check_heredoc(aux[0]) != 0)
		return (-1);
	if (pipe(fd) == -1)
	{
		mini_perror(PIPERR, NULL, 1);
		return (-1);
	}
	str[1] = get_here_str(str, 0, aux[0], aux[1]);
	write(fd[WRITE_END], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(fd[WRITE_END]);
	if (g_status == 1)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
