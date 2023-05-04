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
