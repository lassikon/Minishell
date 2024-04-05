/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:46:25 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/05 14:33:52 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_without_args(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->env)
		return ;
	while (shell->env[i])
	{
		printf("declare -x %s\n", shell->env[i]);
		i++;
	}
}

void	env(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->env)
		return ;
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
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
		export_without_args(shell);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		unset(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		cd(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		ft_exit(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		env(shell);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		pwd(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		echo(shell, cmd);
	else
		return (0);
	return (1);
}
