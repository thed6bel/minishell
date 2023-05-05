//TEST OK PAS DE LEAKS
#include "../minishell.h"

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
	//printf("mod = %d\n", mod);
	if (mod == 1 && cmd->cmd[i] != NULL)
		ft_mod_ok(cmd);
	else
		ft_mod_ko(cmd);
	//set variable globale de status
}
/*
int main(int argc, char **argv, char **envp)
{

	ft_builtin_pwd()
}*/
int main(void)
{
    t_data cmd;
    cmd.path = "echo";
    char *args[] = {"echo", "-n", "test1", NULL};
    cmd.cmd = args;
    cmd.fd_in = 0;
    cmd.fd_out = 1;
    ft_buildin_echo(&cmd);
	system("leaks test");
    return 0;
}
