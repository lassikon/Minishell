/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:36:20 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/08 14:55:43 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_env_entrie(t_shell *shell, char *pwd_type)
{
	char	*pwd_path;
	char	*pwd_entry;

	pwd_path = NULL;
	pwd_entry = NULL;
	if (ft_strcmp(pwd_type, "PWD") == 0)
		pwd_path = getcwd(NULL, 0);
	else if (ft_strcmp(pwd_type, "OLDPWD") == 0)
		pwd_path = ft_getenv(shell, "PWD");
	if (!pwd_path)
		return (NULL);
	remove_from_array(shell->env, pwd_type);
	if (ft_strcmp(pwd_type, "PWD") == 0)
		pwd_entry = ft_strjoin("PWD=", pwd_path);
	else if (ft_strcmp(pwd_type, "OLDPWD") == 0)
		pwd_entry = ft_strjoin("OLDPWD=", pwd_path);
	if (!pwd_entry)
	{
		free(pwd_path);
		error(shell, MALLOC, FATAL, 1);
	}
	free(pwd_path);
	return (pwd_entry);
}

void	update_wd(t_shell *shell)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = create_env_entrie(shell, "OLDPWD");
	if (!oldpwd)
		return ;
	pwd = create_env_entrie(shell, "PWD");
	if (!pwd)
	{
		free(oldpwd);
		return ;
	}
	shell->env = add_to_array(shell, shell->env, pwd);
	shell->env = add_to_array(shell, shell->env, oldpwd);
	free(oldpwd);
	free(pwd);
}

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
