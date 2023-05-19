/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:54:31 by marvin            #+#    #+#             */
/*   Updated: 2023/05/19 10:18:42 by lowathar         ###   ########.fr       */
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
# include <errno.h>
# include <sys/ioctl.h>

# define READ_END 0
# define WRITE_END 1

extern int	g_status;
int			g_status;

typedef struct 		s_env
{
    char 			*var;
    char 			equal;
    char 			*value;
    struct 			s_env *next;
} 					t_env;

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

enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

// parse_args.c
void	*ft_check_args(char *out, t_prompt *p);
char	**ft_cmdtrim(char const *s, char *set);

// subsplit.c
char	**split_all(char **args, t_prompt *p);
char	**ft_subsplit(char const *s, char *set);

// matrix_utils.c
char	**ft_matrix_replace_in(char ***big, char **small, int n);
int		ft_matrixlen(char **m);
void	ft_free_matrix(char ***m);
char	**ft_dup_matrix(char **m);
char	**ft_extend_matrix(char **in, char *newstr);

// utils.c
int		ft_strchars_i(const char *s, char *set);
int		ft_strchr_i(const char *s, int c);
void	free_content(void *content);
void	print_cmds(t_prompt *prompt);

// fill_node.c
t_list	*fill_node(char **args, int i);

// strtrim.c
char	*ft_strtrim_all(char const *s1, int squote, int dquote);

// get_params.c
int		get_fd(int oldfd, char *path, int flags[2]);
t_mini	*get_outfile_double(t_mini *node, char **args, int *i);
t_mini	*get_outfile_single(t_mini *node, char **args, int *i);
t_mini	*get_infile_single(t_mini *node, char **args, int *i);
t_mini	*get_infile_double(t_mini *node, char **args, int *i);

// expand.c
char	*expand_path(char *str, int i, int quotes[2], char *var);
char	*expand_vars(char *str, int i, int quotes[2], t_prompt *prompt);

// env.c
char	*mini_getenv(char *var, char **envp, int n);
char	**mini_setenv(char *var, char *value, char **envp, int n);

// prompt.c
char	*ft_getprompt(t_prompt prompt);

// heredoc.c
int		get_here_doc(char *str[2], char *aux[2]);
char	*get_here_str(char *str[2], size_t len, char *limit, char *warn);

// get_path.c
int		builtin(t_prompt *prompt, t_list *cmd, int n);
int		is_builtin(t_mini *n);

// error.c
void	*mini_perror(int err_type, char *param, int err);

// exec.c
void	ft_execute_commandes(t_prompt *p, t_mini *n);
void	ft_cmd_not_found(char **cmd);
void	ft_free(char **str);

#endif
