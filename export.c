/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:43:33 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/28 11:09:07 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	invalid_identifier(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]))
		return (1);
	while (arg[i] && arg[i] != '=')
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
	if (shell->cmd_count > 1)
		return ;
	while (cmd->args[i])
	{
		if (invalid_identifier(cmd->args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			error(shell, "': not a valid identifier", ERROR, 1);
		}
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
