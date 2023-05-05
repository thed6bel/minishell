/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:41:09 by hucorrei          #+#    #+#             */
/*   Updated: 2023/05/03 09:28:25 by hucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*stress si cmd = echo "-nnnn test"
dans bash ca print -nnnn test
alors que echo -nnnn test
dans bash print testLEPROMPT
si dans le parsing ont retire les "" ont perd l'info et donc ont prend l'option -n en compte
*/

void	ft_mod_ok(t_data *cmd)//avec options -n
{
	int i;

	i = 2;
	while (cmd->cmd[i] != NULL)
	{
		write(cmd->fd_out, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		i++;
		if (cmd->cmd[i] != NULL)
			write(cmd->fd_out, " ", 1);
	}
}
void	ft_mod_ko(t_data *cmd)
{
	int i;

	i = 1;
	while (cmd->cmd[i] != NULL)
	{
		write(cmd->fd_out, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		i++;
		if (cmd->cmd[i] != NULL)
			write(cmd->fd_out, " ", 1);
	}
	write(cmd->fd_out, "\n", 1);
}

void	ft_set_mod(int *mod, t_data *cmd)
{
	int i;

	i = 1;
	if (cmd->cmd[i] == NULL)
		return;
	if (cmd->cmd[1][0] == '-' && cmd->cmd[1][i] == 'n')
	{
		printf("ft set mod debut\n");
		while (cmd->cmd[1][i] == 'n')
			i++;
		if (cmd->cmd[1][i] != '\0')
			return;
		else
			*mod = 1;
	}
}

void	ft_buildin_echo(t_data *cmd)
{
	int i;
	int mod;

	i = 1;
	mod = 0;
	ft_set_mod(&mod, cmd);
	printf("mod = %d\n", mod);
	if (mod == 1 && cmd->cmd[i] != NULL)
		ft_mod_ok(cmd);
	else
		ft_mod_ko(cmd);
	//set variable globale de status
}

//test ok