/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:54:31 by marvin            #+#    #+#             */
/*   Updated: 2023/04/24 11:54:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"
# include "colors.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}			t_prompt;


typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_mini;

// parse_args.c
void		*ft_check_args(char *out, t_prompt *p);
char		**ft_cmdtrim(char const *s, char *set);

// subsplit.c
char	**ft_parse_args(char **args, t_prompt *p);
char	**ft_subsplit(char const *s, char *set);

// matrix_utils.c
char	**ft_matrix_replace_in(char ***big, char **small, int n);
int		ft_matrixlen(char **m);
void	ft_free_matrix(char ***m);
char	**ft_dup_matrix(char **m);
void	free_content(void *content);
char	**ft_extend_matrix(char **in, char *newstr);

// fill_node.c
t_list  *fill_node(char **args, int i);

// strtrim.c
char	*ft_strtrim_all(char const *s1, int squote, int dquote);

// get_params.c
int	get_fd(int oldfd, char *path, int flags[2]);
t_mini	*get_outfile_double(t_mini *node, char **args, int *i);
t_mini	*get_outfile_single(t_mini *node, char **args, int *i);
t_mini	*get_infile_single(t_mini *node, char **args, int *i);
t_mini  *get_infile_double(t_mini *node, char **args, int *i);


#endif