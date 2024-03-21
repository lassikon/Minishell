/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:43:33 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/21 13:09:14 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	invalid_identifier(t_shell *shell, char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[0] == '=' || (arg[i] != '_' && !ft_isalnum(arg[i])))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			shell->exit_status = 1;
			return (1);
		}
		i++;
	}
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
		return (0);
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
			return (1);
		}
		i++;
	}
	free(identifier);
	return (1);
}

void	export(t_shell *shell, t_cmd *cmd)
{
	int		i;

	i = 1;
	if (shell->cmd_count > 1)
		return ;
	while (cmd->args[i])
	{
		if (invalid_identifier(shell, cmd->args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			error(shell, "': not a valid identifier", ERROR, 1);
		}
		else
		{
			if (!add_to_existing(shell, cmd->args[i]))
			{
				remove_existing(shell, cmd->args[i]);
				shell->env = add_to_array(shell->env, cmd->args[i]);
				if (shell->env == NULL)
					error(shell, MALLOC, FATAL, 1);
			}
		}
		i++;
	}
}
