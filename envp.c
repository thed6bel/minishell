/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thed6bel <thed6bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:38:20 by thed6bel          #+#    #+#             */
/*   Updated: 2023/05/01 09:52:46 by thed6bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Arefairepour le times

#include "../../minishell.h"

typedef struct s_env {
    char *var;
    char equal;
    char *value;
    struct s_env *next;
} t_env;

static int	count_env(t_env *env)
{
    int		count;
    t_env	*curr;

    count = 0;
    curr = env;
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }
    return (count);
}

static void	create_cmd_str(char **cmd, t_env *env)
{
    t_env	*curr;
    int		i;
    size_t	var_len;
    size_t	value_len;

    curr = env;
    i = 0;
    while (curr != NULL)
    {
        var_len = ft_strlen(curr->var);
        value_len = (curr->value != NULL && curr->value[0] != NULL) ? ft_strlen(curr->value[0]) : 0;
        cmd[i] = (char *)malloc(sizeof(char) * (var_len + value_len + 2));
        if (cmd[i] == NULL)
            return ;
        ft_strlcpy(cmd[i], curr->var, var_len + 1);
        ft_strlcat(cmd[i], "=", var_len + 2);
        if (value_len > 0)
        {
            ft_strlcat(cmd[i], curr->value[0], var_len + value_len + 2);
        }
        curr = curr->next;
        i++;
    }
}

static void free_str_array(char **array)
{
    char	**p;

    p = array;
    while (*p != NULL)
    {
        free(*p);
        *p = NULL;
        p++;
    }
    free(array);
}

char	**env_to_array(t_env *env)
{
    int		count;
    char	**cmd;

    count = count_env(env);
    cmd = (char **)malloc(sizeof(char *) * (count + 1));
    if (cmd == NULL)
        return (NULL);
    cmd[count] = NULL;
    create_cmd_str(cmd, env);
    return (cmd);
}

static t_env	*create_env_entry(char *env_line)
{
    int		var_len;
    t_env	*new_entry;

    new_entry = (t_env *)malloc(sizeof(t_env));
    if (new_entry == NULL)
        return (NULL);
    new_entry->equal = '=';
    new_entry->next = NULL;

    char *equal_pos = ft_strchr(env_line, '=');
    if (equal_pos != NULL)
    {
        var_len = equal_pos - env_line;
        new_entry->var = ft_substr(env_line, 0, var_len);
        new_entry->value = ft_split(equal_pos + 1, ':');
        if (new_entry->var == NULL || new_entry->value == NULL)
        {
            free(new_entry->var);
            free(new_entry->value);
            free(new_entry);
            return (NULL);
        }
    }
    return (new_entry);
}

static t_env	*add_env_entry(t_env *head, t_env *tail, t_env *new_entry)
{
    if (new_entry == NULL)
        return (head);
    if (head == NULL)
    {
        head = new_entry;
        tail = new_entry;
    }
    else
    {
        tail->next = new_entry;
        tail = new_entry;
    }
    return (head);
}

t_env	*get_env_list(char **envp)
{
    int		i;
    t_env	*new_entry;
    t_env	*head;
    t_env	*tail;

    head = NULL;
    tail = NULL;

    if (envp == NULL || *envp == NULL)
        return (NULL);

    i = 0;
    while (envp[i] != NULL)
    {
        new_entry = create_env_entry(envp[i]);
        if (new_entry != NULL)
        {
            head = add_env_entry(head, tail, new_entry);
            tail = new_entry;
        }
        i++;
    }
    return (head);
}

int main(int argc, char **argv, char **envp)
{
    t_env *env_list = get_env_list(envp);

    // Test get_env_list
    t_env *current = env_list;
    while (current != NULL)
    {
        printf("%s%c%s\n", current->var, current->equal, current->value != NULL && current->value[0] != NULL ? current->value[0] : "");
        current = current->next;
    }

    // Test env_to_array
    char **env_array = env_to_array(env_list);
    int i = 0;
    printf("\ndouble tab:\n\n");
    while (env_array[i] != NULL)
    {
        printf("%s\n", env_array[i]);
        i++;
    }

    // Cleanup
    free_str_array(env_array);

    return (0);
}
