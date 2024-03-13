/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:46:25 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/13 16:43:45 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_identifier(t_shell *shell, char *arg)
{
	char	*identifier;

	if (ft_strchr(arg, '='))
		identifier = ft_substr(arg, 0, ft_strchr(arg, '=') - arg + 1);
	else
		identifier = ft_strdup(arg);
	if (identifier == NULL)
		error(shell, MALLOC, FATAL, 1);
	if (ft_strchr(identifier, '-'))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(identifier, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(identifier);
		shell->exit_status = 1;
		return (1);
	}
	free(identifier);
	return (0);
}

static void	check_existing(t_shell *shell, char *arg)
{
	char	*identifier;
	int		i;

	identifier = ft_substr(arg, 0, ft_strchr(arg, '=') - arg + 1);
	if (identifier == NULL)
		error(shell, MALLOC, FATAL, 1);
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
	free(identifier);
}

static void	export(t_shell *shell, t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		if ((cmd->args[i][0] == '=') || ft_isdigit(cmd->args[i][0]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			error(shell, "': not a valid identifier", ERROR, 1);
		}
		else
		{
			if (check_identifier(shell, cmd->args[i]))
				return ;
			check_existing(shell, cmd->args[i]);
			shell->env = add_to_array(shell->env, cmd->args[i]);
			if (shell->env == NULL)
				error(shell, MALLOC, FATAL, 1);
		}
		i++;
	}
}

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

int	child_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "export", 7) == 0 && !cmd->args[1])
		env(shell, 1);
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

int	parent_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "export", 7) == 0 && cmd->args[1])
		export(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		unset(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		cd(shell, cmd);
	else if (ft_strncmp(shell->line, "exit", 4) == 0)
		ft_exit(shell, cmd);
	else
		return (0);
	return (1);
}
