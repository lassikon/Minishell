/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:40:22 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/10 14:58:08 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	find_in_env(char **env, char *identifier)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(identifier);
	while (env[i])
	{
		if (ft_strncmp(env[i], identifier, len) == 0)
		{
			if (env[i][len] == '\0' || env[i][len] == '=')
				return (1);
		}
		i++;
	}
	return (0);
}

void	unset(t_shell *shell, t_cmd *cmd)
{
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
			if (find_in_env(shell->env, cmd->args[i]))
				remove_from_array(shell->env, cmd->args[i]);
		}
		i++;
	}
}
