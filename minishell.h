/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:22:13 by hucorrei          #+#    #+#             */
/*   Updated: 2023/04/14 14:02:20 by hucorrei         ###   ########.fr       */
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
	char			*path;
	char			**cmd;
	int 			fd_in;
	int				fd_out;
	struct s_data	*next;//liste chainee vs **tab de struct
}					t_data;

typedef struct 		s_shell
{
	//char			**builtins;
	char			*cmds;
	pid_t			pid;
	char			**envp;
	char			*shell_prompt;
	t_data			data_cmd;
	int				exit_stat;
}					t_shell;


# endif