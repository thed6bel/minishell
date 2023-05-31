/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:10:18 by lowathar          #+#    #+#             */
/*   Updated: 2023/05/31 11:32:38 by hucorrei         ###   ########.fr       */
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

t_env	*get_env_list(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_entry;
	char	*equal_pos;
	int		i;
	int		var_len;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		equal_pos = ft_strchr(envp[i], '=');
		if (equal_pos != NULL)
		{
			new_entry = (t_env *)malloc(sizeof(t_env));
			if (new_entry == NULL)
				return (NULL);
			var_len = equal_pos - envp[i];
			new_entry->var = ft_substr(envp[i], 0, var_len);
			new_entry->equal = '=';
			new_entry->value = ft_strdup(equal_pos + 1);
			if (new_entry->var == NULL || new_entry->value == NULL)
			{
				free(new_entry->var);
				free(new_entry->value);
				free(new_entry);
				return (NULL);
			}
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
	return (head);
}

char	**env_list_to_tab(t_env *envp)
{
	int		count;
	int		len;
	char	**env;
	t_env	*current;
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
		len = ft_strlen(current->var) + 1 + ft_strlen(current->value) + 1;
		env[i] = malloc(sizeof(char) * len);
		if (!env[i])
			return (NULL);
		ft_strlcpy(env[i], current->var, len);
		env[i][ft_strlen(current->var)] = '=';
		ft_strlcpy(env[i] + ft_strlen(current->var) + 1, current->value, len - ft_strlen(current->var) - 1);
		current = current->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
