/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:46:25 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/20 13:47:07 by lkonttin         ###   ########.fr       */
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

static void	remove_existing(t_shell *shell, char *arg)
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

static int	add_to_existing(t_shell *shell, char *arg)
{
	char	*identifier;
	int		i;
	int		end;

	end = 0;
	while (arg[end] && arg[end] != '=')
		end++;
	if (arg[end - 1] != '+')
		return (1);
	identifier = ft_strjoin(ft_substr(arg, 0, end - 1), "=");
	if (identifier == NULL)
		error(shell, MALLOC, FATAL, 1);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], identifier, ft_strlen(identifier)) == 0)
		{
			shell->env[i] = join_n_free(shell->env[i], ft_substr(arg, end + 1, ft_strlen(arg) - end));
			if (shell->env[i] == NULL)
				error(shell, MALLOC, FATAL, 1);
			free(identifier);
			return (0);
		}
		i++;
	}
	free(identifier);
	return (0);
}

static void	export(t_shell *shell, t_cmd *cmd)
{
	int		i;

	i = 1;
	if (shell->cmd_count > 1)
		return ;
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
			if (add_to_existing(shell, cmd->args[i]))
			{
				remove_existing(shell, cmd->args[i]);
				shell->env = add_to_array(shell->env, cmd->args[i]);
			}
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
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0 && shell->cmd_count > 1)
		ft_exit(shell, cmd);
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
