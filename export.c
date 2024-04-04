/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:43:33 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/04 15:36:29 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	invalid_export_identifier(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] != '_' && !ft_isalnum(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	invalid_unset_identifier(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	while (arg[i])
	{
		if (arg[i] != '_' && !ft_isalnum(arg[i]))
			return (1);
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

void	export(t_shell *shell, t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		if (invalid_export_identifier(cmd->args[i]))
			export_error_msg(shell, cmd->args[i], EXPORT);
		else
		{
			remove_existing(shell, cmd->args[i]);
			shell->env = add_to_array(shell->env, cmd->args[i]);
			if (shell->env == NULL)
				error(shell, MALLOC, FATAL, 1);
		}
		i++;
	}
}

void	unset(t_shell *shell, t_cmd *cmd)
{
	char	*identifier;
	int		i;

	i = 1;
	if (!cmd->args[i])
		return ;
	while (cmd->args[i])
	{
		if (invalid_unset_identifier(cmd->args[i]))
			export_error_msg(shell, cmd->args[i], UNSET);
		else
		{
			identifier = ft_strjoin(cmd->args[i], "=");
			if (identifier == NULL)
				error(shell, MALLOC, FATAL, 1);
			if (find_in_array(shell->env, identifier))
				remove_from_array(shell->env, identifier);
			free(identifier);
		}
		i++;
	}
}
