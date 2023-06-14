/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thed6bel <thed6bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:18:28 by thed6bel          #+#    #+#             */
/*   Updated: 2023/05/22 17:19:31 by thed6bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
				q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
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

static	void	*parse_arg(char **args, t_prompt *p)
{
	p->cmds = fill_node(split_all(args, p), -1);
	if (!p->cmds)
		return (p);
	builtin(p, p->cmds);
	return (p);
}

void	*ft_check_args(char *out, t_prompt *p)
{
	char	**a;

	if (out && out[0] && out[0] != '\0')
		add_history(out);
	a = ft_cmdtrim(out, " ");
	if (!a)
	{
		mini_perror(QUOTE, NULL, 1);
		return ("");
	}
	//system("leaks minishell");
	p = parse_arg(a, p);
	ft_execute_commandes(p);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_content);
	return (p);
}
