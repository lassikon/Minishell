/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:43:33 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/10 16:34:51 by lkonttin         ###   ########.fr       */
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

int	exists_in_env(char **env, char *id)
{
	int	i;
	int	k;

	i = 0;
	while (env[i])
	{
		k = 0;
		if (env[i][k] == id[k])
		{
			while (env[i][k] && id[k] && env[i][k] == id[k] && env[i][k] != '=')
				k++;
			if (id[k] == '\0' && env[i][k] == '=')
				return (-1);
			if (env[i][k] == '\0' && id[k] == '=')
				return (1);
			if (env[i][k] == '\0' && id[k] == '\0')
				return (1);
			if (env[i][k] == '=' && id[k] == '=')
				return (1);
		}
		i++;
	}
	return (0);
}

static void	remove_existing(t_shell *shell, char *arg)
{
	char	*identifier;
	int		len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	identifier = ft_substr(arg, 0, len);
	if (identifier == NULL)
		error(shell, MALLOC, FATAL, 1);
	remove_from_array(shell->env, identifier);
	free(identifier);
	return ;
}

static void	export_without_args(t_shell *shell)
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

void	export(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		ret;

	i = 1;
	if (!cmd->args[i])
	{
		export_without_args(shell);
		return ;
	}
	while (cmd->args[i] && shell->status != ERROR)
	{
		if (invalid_export_identifier(cmd->args[i]))
			export_error_msg(shell, cmd->args[i], EXPORT);
		else
		{
			ret = exists_in_env(shell->env, cmd->args[i]);
			if (ret >= 0)
			{
				if (ret == 1)
					remove_existing(shell, cmd->args[i]);
				shell->env = add_to_array(shell, shell->env, cmd->args[i], 0);
			}
		}
		i++;
	}
}
