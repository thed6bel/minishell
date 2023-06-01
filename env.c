/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:10:18 by lowathar          #+#    #+#             */
/*   Updated: 2023/06/01 10:15:48 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*mini_getenv(char *var, char **envp, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_i(envp[i], '='))
			n2 = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

char	**mini_setenv(char *var, char *value, char **envp, int n)
{
	int		i[2];
	char	*aux[2];

	if (n < 0)
		n = ft_strlen(var);
	i[0] = -1;
	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		i[1] = n;
		if (i[1] < ft_strchr_i(envp[i[0]], '='))
			i[1] = ft_strchr_i(envp[i[0]], '=');
		if (!ft_strncmp(envp[i[0]], var, i[1]))
		{
			aux[0] = envp[i[0]];
			envp[i[0]] = aux[1];
			free(aux[0]);
			return (envp);
		}
	}
	envp = ft_extend_matrix(envp, aux[1]);
	free(aux[1]);
	return (envp);
}

t_env	*create_env_entry(char *equal_pos, char **envp, int i, int j)
{
	t_env	*new_entry;

	new_entry = (t_env *)malloc(sizeof(t_env));
	if (new_entry == NULL)
		return (NULL);
	i = equal_pos - envp[j];
	new_entry->var = ft_substr(envp[j], 0, i);
	new_entry->equal = '=';
	new_entry->value = ft_strdup(equal_pos + 1);
	if (new_entry->var == NULL || new_entry->value == NULL)
	{
		free_env_list(new_entry);
		return (NULL);
	}
	new_entry->next = (NULL);
	return (new_entry);
}

t_env	*get_env_list(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_entry;
	char	*equal_pos;
	int		i[2];

	head = NULL;
	tail = NULL;
	i[0] = 0;
	while (envp[i[0]] != NULL)
	{
		equal_pos = ft_strchr(envp[i[0]], '=');
		if (equal_pos != NULL)
		{
			new_entry = create_env_entry(equal_pos, envp, i[1], i[0]);
			add_env_entry(&head, &tail, new_entry);
		}
		i[0]++;
	}
	return (head);
}

char	**env_list_to_tab(t_env *envp)
{
	int		count;
	t_env	*current;
	char	**env;
	int		i;

	count = 0;
	current = envp;
	while (current)
	{
		count++;
		current = current->next;
	}
	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	current = envp;
	i = 0;
	while (current)
	{
		fill_env_tab(env, current, i);
		current = current->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
