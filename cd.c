/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:36:20 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/10 15:07:18 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_oldpwd(t_shell *shell, char **path)
{
	char	*oldpwd;

	oldpwd = ft_getenv(shell, "OLDPWD");
	if (!oldpwd)
		return (error(shell, "cd: OLDPWD not set", ERROR, 1));
	*path = oldpwd;
	return (0);
}

static int	cd_home(t_shell *shell, char *arg, char **path)
{
	char	*home;

	home = ft_getenv(shell, "HOME");
	if (!home)
		return (error(shell, "cd: HOME not set", ERROR, 1));
	if (!arg || (arg[0] == '~' && !arg[1]))
		*path = home;
	else if (arg[0] == '~' && arg[1])
	{
		*path = ft_strjoin(home, &arg[1]);
		free(home);
		if (!*path)
		{
			free(home);
			return (error(shell, MALLOC, FATAL, 1));
		}
	}
	return (0);
}

void	cd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	if (!cmd->args[1] || cmd->args[1][0] == '~')
	{
		if (cd_home(shell, cmd->args[1], &path))
			return ;
	}
	else if (cmd->args[1][0] == '-' && !cmd->args[1][1])
	{
		if (cd_oldpwd(shell, &path))
			return ;
	}
	else
	{
		path = ft_strdup(cmd->args[1]);
		if (!path)
			error(shell, MALLOC, FATAL, 1);
	}
	if (chdir(path) == -1)
		cd_error(shell, path);
	else
		update_wd(shell);
	free(path);
}
