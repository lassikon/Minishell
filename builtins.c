/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:46:25 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/04 14:36:47 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_shell *shell, int export)
{
	int	i;
	int	k;

	i = 0;
	if (!shell->env)
		return ;
	while (shell->env[i])
	{
		if (export)
		{
			k = 0;
			write(1, "declare -x ", 11);
			while (shell->env[i][k] && shell->env[i][k] != '=')
			{
				write(1, &shell->env[i][k], 1);
				k++;
			}
			printf("=\"%s\"\n", &shell->env[i][k + 1]);
		}
		else
			printf("%s\n", shell->env[i]);
		i++;
	}
}

void	pwd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	(void)cmd;
	path = ft_getenv(shell, "PWD");
	if (!path)
	{
		path = getcwd(NULL, 0);
	}
	printf("%s\n", path);
	if (path)
		free(path);
}

int	check_builtin(t_cmd *cmd)
{
	if (cmd->cmd == NULL)
		return (0);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		return (1);
	else
		return (0);
}

int	run_builtin(t_shell *shell, t_cmd *cmd)
{
	if (cmd->cmd == NULL)
		return (0);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0 && cmd->args[1])
		export(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0 && !cmd->args[1])
		env(shell, 1);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		unset(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		cd(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		ft_exit(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		env(shell, 0);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		pwd(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		echo(shell, cmd);
	else
		return (0);
	return (1);
}
