/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thed6bel <thed6bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:19:27 by hucorrei          #+#    #+#             */
/*   Updated: 2023/06/05 17:55:26 by thed6bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_handler(int n)
{
	struct termios	term;

	if (n == SIGINT)
	{
		g_status = 130;
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag &= ~ECHOCTL;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ft_handler_process(int n)
{
	if (n == SIGINT)
	{
		g_status = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
	}
	else if (n == SIGQUIT)
	{
		g_status = 131;
		write(STDOUT_FILENO, "Quit\n", 5);
		rl_replace_line("", 0);
	}
}

void	ft_signal(void)
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signals_inprocess(void)
{
	signal(SIGINT, ft_handler_process);
	signal(SIGQUIT, ft_handler_process);
}
