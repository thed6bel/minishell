#include "../minishell.h"

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

char *ft_set_var(char *arg)
{
	int i;
	int size;
	char *res;

	i = 0;
	size = 0;
	while (arg[size] && arg[size] != '=')
		size++;
	if (!arg[size])
		return(arg);
    if (size == 0)
        return (NULL);
	res = malloc(sizeof(char) * size + 1);
	if (!res)
		return (NULL);
	while (i < size)
	{
		res[i] = arg[i];
		i++;
	}
	res[i] = '\0';
    //printf("ft SET VAR : %s\n", res);
	return (res);
}

char *ft_set_value(char *arg)
{
	int i;
	int size;
	char *res;
	char *tmp;

	i = 0;
	size = 0;
	tmp = arg;
	while(*tmp && *tmp != '=')
		tmp++;
	if (*tmp == '=')
		tmp++;
    else
        return (NULL);
	while (tmp[size])
		size++;
	res = malloc(sizeof(char *) * size +1);
	if (!res)
		return(NULL);
	while (i < size)
	{
		res[i] = tmp[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void    ft_new_list(char *var, char *value, t_env *buff)
{
	t_env *tmp;
	t_env *new;

	tmp = buff;
	new = malloc(sizeof(t_env));
	if (!new)
		return;
	tmp->next = new;
	new->next = NULL;
	new->var = var;
    if (value)
	    new->equal = '=';
	new->value = value;    
	//printf("NEW LIST END : %s%c%s\n", new->var, new->equal, new->value);
}

void	ft_swap_env(t_env *env1, t_env *env2)
{
	char *var_tmp;
	char equal_tmp;
	char *value_tmp;
	
	var_tmp = env1->var;
    equal_tmp = env1->equal;
    value_tmp = env1->value;

    env1->var = env2->var;
    env1->equal = env2->equal;
    env1->value = env2->value;

    env2->var = var_tmp;
    env2->equal = equal_tmp;
    env2->value = value_tmp;	
}

void	ft_sort_list(t_env *envpcpy)
{
	int swap;
	t_env *tmp;
	t_env *list;

	list = NULL;
	swap = 1;
	while (swap)
	{
		swap = 0;
		tmp = envpcpy;
		while (tmp->next != list)
		{
			if (ft_strncmp(tmp->var, tmp->next->var, ft_strlen(tmp->var) + 1) > 0)
			{
				ft_swap_env(tmp, tmp->next);
				swap = 1;	
			}
			tmp = tmp->next;
		}
		list = tmp;
	}
}
/*
void ft_print_export(t_data *cmd, t_env *envp)
{
	//prendre envp et le mettre par ordre alpha!!
	t_env *envpcpy;
	t_env *tmp;
	t_env *new_env;

	envpcpy = NULL;
	tmp = NULL;
	new_env = NULL;

	while (envp)
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			return;
		new_env->var = ft_strdup(envp->var);
		new_env->equal = envp->equal;
		new_env->value = envp->value ? ft_strdup(envp->value) : NULL;
		new_env->next = NULL;
		if (envpcpy == NULL)
		{
			envpcpy = new_env;
			tmp = new_env;
		}
		else
		{
			tmp->next = new_env;
			tmp = tmp->next;
		}
		envp = envp->next;
	}
	ft_sort_list(envpcpy);
	while (envpcpy)
	{
		write(cmd->fd_out, "declare -x ", 11);
		write(cmd->fd_out, envpcpy->var, ft_strlen(envpcpy->var));
		if (envpcpy->value)
		{
			write(cmd->fd_out, "=\"", 2);
			write(cmd->fd_out, envpcpy->value, ft_strlen(envpcpy->value));
			write(cmd->fd_out, "\"", 1);
		}
		write(cmd->fd_out, "\n", 1);
		t_env *tmp = envpcpy;
		envpcpy = envpcpy->next;
		free(tmp->var);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}*/

void ft_print_export(t_data *cmd, t_env *envp)
{
    t_env *envpcpy;
    t_env *tmp;
    t_env *new_env;

    envpcpy = NULL;
    tmp = NULL;
    new_env = NULL;

    while (envp)
    {
        new_env = malloc(sizeof(t_env));
        if (!new_env)
            return;
        new_env->var = ft_strdup(envp->var);
        new_env->equal = envp->equal;
        new_env->value = envp->value ? ft_strdup(envp->value) : NULL;
        new_env->next = NULL;
        if (envpcpy == NULL)
        {
            envpcpy = new_env;
            tmp = new_env;
        }
        else
        {
            tmp->next = new_env;
            tmp = tmp->next;
        }
        envp = envp->next;
    }

    ft_sort_list(envpcpy);

    while (envpcpy)
    {
        if (!(envpcpy->var[0] == '_' && envpcpy->value[0] == '/'))
        {
            write(cmd->fd_out, "declare -x ", 11);
            write(cmd->fd_out, envpcpy->var, ft_strlen(envpcpy->var));
            if (envpcpy->value)
            {
                write(cmd->fd_out, "=\"", 2);
                write(cmd->fd_out, envpcpy->value, ft_strlen(envpcpy->value));
                write(cmd->fd_out, "\"", 1);
            }
            write(cmd->fd_out, "\n", 1);
        }
        t_env *tmp = envpcpy;
        envpcpy = envpcpy->next;
        free(tmp->var);
        if (tmp->value)
            free(tmp->value);
        free(tmp);
    }
}

void	built_export(t_data *cmd, t_env *envp)
{
	t_env *buff;
	char *var;
	char *value;
	int i;

	buff = envp;
	i = 1;
	//protec NULL return
	if (cmd->cmd[1] == NULL)
    {
		ft_print_export(cmd, envp);//ok ca focntionne //declare -x PWD="/home/thed6bel/projet/test/minishell/louis/minishell" sous linux pareil sous bash
        return;
    }
    else
    {
		while (cmd->cmd[i])
		{
			var = ft_set_var(cmd->cmd[i]);
			value = ft_set_value(cmd->cmd[i]);
			if (!var)
			{
				printf("not a valide command, use : export [name=value]\n");
				return;
			}
			while (buff->next != NULL)
				buff = buff->next;
			if (buff->next == NULL)
				ft_new_list(var, value, buff);
			i++;
		}
    }
    //free(buff->value);
    //free(var);
    //buff->value = value;
	//print la liste d'env pour ctrl et puis par ordre juste pour le teste
}

int main(int argc, char **argv, char **envp)
{
    t_data *cmd = malloc(sizeof(t_data));
    cmd->path = "export";
    cmd->cmd = malloc(sizeof(char*)*4);
    cmd->cmd[0] = "export";
    cmd->cmd[1] = "atchoum=42";
	cmd->cmd[2] = NULL;
    cmd->cmd[3] = NULL;
    cmd->fd_in = 0;
    cmd->fd_out = 1;
    cmd->pid = getpid();
    cmd->next = NULL;

    t_env *env_list = get_env_list(envp);
    built_export(cmd, env_list);
    ft_print_export(cmd, env_list);//SI COMMENTER = 0 LEAKS

    // Freeing allocated memory
    /*t_env *tmp;
    while (env_list != NULL)
    {
        tmp = env_list;
        env_list = env_list->next;
        //free(tmp->var);
        //free(tmp->value);
        free(tmp);
    }
    free(cmd->cmd);
    free(cmd);*/
    //system("leaks test");
    return 0;
}
