/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:22:13 by hucorrei          #+#    #+#             */
/*   Updated: 2023/03/31 09:54:36 by hucorrei         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef struct 		s_cmds
{
	char			*cmd;
	char			**args;
	struct s_cmds	*next;
}					t_cmds;


# endif