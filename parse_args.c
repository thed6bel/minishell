/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:33:42 by marvin            #+#    #+#             */
/*   Updated: 2023/04/24 12:33:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern  int status;

static int	ft_count_words(const char *s, char *c, int i[2])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s[i[0]] != '\0')
	{
		if (!ft_strchr(c, s[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0')
			{
				if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
					q[1] = s[i[0]];
				if (s[i[0]] == q[1])  // q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
					q[0] = !q[0];	
				else
					q[0] = q[0];
				if (q[0] != 0) // 	q[1] *= q[0] != 0;
					q[1] *= 1;
				else
					q[1] *= 0;
				i[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static char	**ft_fill_array(char **aux, char const *s, char *set, int i[3])
{
	int		s_len;
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	s_len = ft_strlen(s);
	while (s[i[0]])
	{
		while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
		{
			q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= s_len)
			aux[i[2]++] = "\0";
		else
			aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (aux);
}

char	**ft_cmdtrim(char const *s, char *set)
{
	char	**aux;
	int		nb_words;
	int		i[3];
	int		counts[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	counts[0] = 0;
	counts[1] = 0;
	if (!s)
		return (NULL);
	nb_words = ft_count_words(s, set, counts);
	if (nb_words == -1)
		return (NULL);
	aux = malloc((nb_words + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	aux = ft_fill_array(aux, s, set, i);
	aux[nb_words] = NULL;
	return (aux);
}

static void print_cmds(t_prompt *prompt)
{
    t_list *cmds = prompt->cmds;
    while (cmds != NULL)
    {
        t_mini *cmd = cmds->content;
        printf("Full command: %s\n", cmd->full_cmd[0]);
        printf("Full path: %s\n", cmd->full_path);
        printf("Input file descriptor: %d\n", cmd->infile);
        printf("Output file descriptor: %d\n", cmd->outfile);
        cmds = cmds->next;
    }
}

void	*ft_check_args(char *out, t_prompt *p)
{
	char **a;
	t_mini *n;
	int i;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	a = ft_cmdtrim(out, " ");
	free(out);
	i = 0;
	while(a[i] != NULL)
	{
		printf("firstsplit[%i] : %s\n", i, a[i]);
		i++;
	}
	//if (!a)
		//error quote
		//return error
	p->cmds = fill_node(ft_parse_args(a, p), -1);
	print_cmds(p);
	//list or table
	i = 0;
	// printf("\n======\n\n");
	// while (p->cmds[i] != NULL)
	// {
	// 	printf("secondsplit[%i] : %s\n", i, p->cmds[i]);
	// 	i++;
	// }
	return (0);
}
