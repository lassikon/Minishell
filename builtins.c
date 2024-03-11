/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:46:25 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/11 11:58:14 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_identifier(t_shell *shell, char *arg)
{
	char	*identifier;
	int		i;

	identifier = ft_substr(arg, 0, ft_strchr(arg, '=') - arg + 1);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], identifier, ft_strlen(identifier)) == 0)
		{
			remove_from_array(shell->env, identifier);
			free(identifier);
			return ;
		}
		i++;
	}
}

static void	export(t_shell *shell, t_cmd *cmd)
{
	int		i;

	i = 1;
	if (!cmd->args[1])
	{
		env(shell);
		exit(0);
	}
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '='))
		{
			check_identifier(shell, cmd->args[i]);
			shell->env = add_to_array(shell->env, cmd->args[i]);
		}
		i++;
	}
}

static void	unset(t_shell *shell, t_cmd *cmd)
{
	char	*identifier;
	int		i;

	if (!cmd->args[1])
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		identifier = ft_strjoin(cmd->args[i], "=");
		if (identifier == NULL)
			exit(1);
		if (find_in_array(shell->env, identifier))
		{
			remove_from_array(shell->env, identifier);
			printf("Unset %s\n", identifier);
		}
		else
			printf("unset: %s: not found\n", identifier);
		free(identifier);
		i++;
	}
}

void	child_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "export", 7) == 0 && !cmd->args[1])
		export(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		env(shell);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		pwd(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		echo(shell, cmd);
	else
		return ;
}

int	parent_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "export", 7) == 0 && cmd->args[1])
		export(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		unset(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		cd(shell, cmd);
	else
		return (0);
	return (1);
}
