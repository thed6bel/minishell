/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:57:15 by marvin            #+#    #+#             */
/*   Updated: 2023/04/24 11:57:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char				*str;
	char				*out;
	t_prompt			prompt;

	while (argv && argc)
	{
	// str = ft_getprompt(prompt);
		if (str)
			out = readline(str);
		else
			out = readline("guest@minishell $ ");
		free(str);
		if (!ft_check_args(out, &prompt))
			break;
	}
	exit(0); // return(status)
}
