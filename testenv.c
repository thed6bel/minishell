/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:53:32 by hucorrei          #+#    #+#             */
/*   Updated: 2023/05/05 15:03:33 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//extern int g_status = 0;

t_env *get_env_list(char **envp)
{
    int i;
    char *equal_pos;
    int var_len;
    t_env *new_entry;
    t_env *head;
    t_env *tail;

    head = NULL;
    tail = NULL;
    if (envp == NULL || *envp == NULL)
        return NULL;
    i = 0;
    while (envp[i] != NULL)
    {
        equal_pos = ft_strchr(envp[i], '=');
        if (equal_pos != NULL)
        {
            new_entry = (t_env *)malloc(sizeof(t_env));
            var_len = equal_pos - envp[i];
            new_entry->var = ft_substr(envp[i], 0, var_len);
            new_entry->equal = '=';
            new_entry->value = ft_strdup(equal_pos + 1);
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
    return head;
}

void	built_env(t_data *cmd, t_env *envp)
{
	t_env *buff;

	buff = envp;
	while (buff != NULL)
	{
		write(cmd->fd_out, buff->var, ft_strlen(buff->var));
		write(cmd->fd_out, "=", 1);
		write(cmd->fd_out, buff->value, ft_strlen(buff->value));
		write(cmd->fd_out, "\n", 1);
		buff = buff->next;
	}
	//if (envp != NULL)
		//g_status = 0;
}

int main(int argc, char **argv, char **envp)
{
    t_data *cmd = malloc(sizeof(t_data));
    cmd->path = "env";
    cmd->cmd = malloc(sizeof(char*)*2);
    cmd->cmd[0] = "env";
    cmd->cmd[1] = "NULL";
    cmd->fd_in = 0;
    cmd->fd_out = 1;
    cmd->pid = getpid();
    cmd->next = NULL;
	
	t_env *env_list = get_env_list(envp);
	
	built_env(cmd, env_list);
	//system("leaks test");
	return (0);
}