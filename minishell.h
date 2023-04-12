/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thed6bel <thed6bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:22:13 by hucorrei          #+#    #+#             */
/*   Updated: 2023/04/11 13:43:51 by thed6bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef struct 		s_data
{
	char			*cmd;
	char			**args;
	int 			fd_i;
	int				fd_o;
	struct s_data	*next;
}					t_data;

typedef struct 		s_shell
{
	//char			**builtins;
	char			*cmds;
	int				pid;
	char			**envp;
}					t_shell;


# endif