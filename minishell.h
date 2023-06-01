/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:03:17 by lowathar          #+#    #+#             */
/*   Updated: 2023/05/26 14:03:17 by lowathar         ###   ########.fr       */
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
# include <termios.h>
# include <sys/types.h>

# define READ_END 0
# define WRITE_END 1

extern int	g_status;
int			g_status;

typedef struct s_env
{
	char			*var;
	char			equal;
	char			*value;
	struct s_env	*next;
}			t_env;

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
void	free_memory(char *str);
char	*read_input(char *str);

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
t_env	*get_env_list(char **envp);
char	**env_list_to_tab(t_env *envp);

// env_utils.c
void	fill_env_tab(char **env, t_env *current, int i);
void	add_env_entry(t_env **head, t_env **tail, t_env *new_entry);

// prompt.c
char	*ft_getprompt(t_prompt prompt);

// heredoc.c
int		get_here_doc(char *str[2], char *aux[2]);
char	*get_here_str(char *str[2], size_t len, char *limit, char *warn);

// get_path.c
int		builtin(t_prompt *prompt, t_list *cmd, int n);
int		is_builtin(t_mini *n);
int		ft_dispatch_builtin(t_mini *n, t_prompt *p);

// error.c
void	*mini_perror(int err_type, char *param, int err);
void	ft_exit(char *a);
void	ft_free(char **str);
void	ft_close_fds(t_mini *cmd);
void	free_env_list(t_env *head);

// exec.c and exec_utils
void	ft_execute_single_command(t_mini *cmd, char **envp);
void	ft_pipe_and_execute(t_list *cur, t_prompt *p, int fds[2], int s_stdout);
void	ft_close_and_restore(int fds[2], int s_stdin, int stdout, t_list *cmds);
void	ft_execute_p_cmds(t_list *cmds, t_prompt *p, t_list *cur, int fds[2]);
void	ft_execute_commandes(t_prompt *p);
void	ft_exec_builtin_helper(t_mini *n, t_env *env_list, t_prompt *p);
int		ft_execute_other_builtins(t_mini *n, t_prompt *p, t_env *env_list);
int		ft_execute_builtin(t_mini *n, t_prompt *p);
void	ft_child_process(t_mini *cmd, char **envp);
void	ft_parent_process(t_mini *cmd, int *status, pid_t pid);

// builtins
char	*ft_gethomedir(t_env *envp);
void	ft_buildin_echo(t_mini *n);
void	built_env(t_mini *n, t_env *envp);
void	ft_builtin_exit(t_mini *n, t_env *env_list);
void	ft_builtin_pwd(t_mini *n);
void	ft_builtin_unset(t_mini *n, t_env **envp);

// builtin_cd and builtin_cd_utils
void	ft_builtin_cd(t_mini *n, t_env *envp);
void	ft_upd_pwd(t_env *envp);
char	*ft_gethomedir(t_env *envp);
char	*ft_compet_path(char *cmd, t_env *envp);
void	get_old_dir(t_env *envp);
char	*get_oldpwd(t_env *envp);
void	ft_make_oldpwd(t_env *envp);

//builtin_export
void	ft_builtin_export(t_mini *n, t_env *envp);
void	ft_check_variable(t_env *buff, char *var, char *value, int *mod);
int		ft_var_error(char *var, char *value, int *mod);
void	ft_print_export(t_mini *n, t_env *envp);
void	ft_print_env(t_mini *n, t_env *envpcpy);
void	ft_copy_env(t_env *envp, t_env **envpcpy, t_env	*tmp, t_env	*new_env);
void	ft_sort_list(t_env *envpcpy);
void	ft_swap_env(t_env *env1, t_env *env2);
void	ft_new_list(char *var, char *value, t_env *buff);
char	*ft_set_value(char *arg);
char	*ft_set_var(char *arg, int *mod);
void	ft_export_mod(char *varfind, char *value1, t_env *buff, int *mod);
int		ft_var_error_print(char *var, char *value);
void	free_env_list(t_env *head);
void	ft_export_mod_utils(char **finalvalue, t_env *current, char *value1);

//signal
void	ft_handler(int n);
void	ft_handler_process(int n);
void	ft_signal(void);
void	ft_signals_inprocess(void);

#endif
