/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:46:25 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/27 11:35:23 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset(t_shell *shell, t_cmd *cmd)
{
	char	*identifier;
	int		i;

	i = 1;
	if (!cmd->args[i])
		return ;
	while (cmd->args[i])
	{
		identifier = ft_strjoin(cmd->args[i], "=");
		if (identifier == NULL)
			error(shell, MALLOC, FATAL, 1);
		if (find_in_array(shell->env, identifier))
			remove_from_array(shell->env, identifier);
		free(identifier);
		i++;
	}
}

int	child_builtin(t_shell *shell, t_cmd *cmd, t_status mode)
{
	if (ft_strncmp(cmd->args[0], "export", 7) == 0 && !cmd->args[1])
	{
		if (mode == EXECUTE)
			env(shell, 1);
	}
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
	{
		if (mode == EXECUTE)
			env(shell, 0);
	}
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
	{
		if (mode == EXECUTE)
			pwd(shell, cmd);
	}
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
	{
		if (mode == EXECUTE)
			echo(shell, cmd);
	}
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0 && shell->cmd_count > 1)
	{
		if (mode == EXECUTE)
			ft_exit(shell, cmd);
	}
	else
		return (0);
	return (1);
}

int	parent_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "export", 7) == 0 && cmd->args[1])
		export(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		unset(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		cd(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0 && shell->cmd_count == 1)
		ft_exit(shell, cmd);
	else
		return (0);
	return (1);
}
