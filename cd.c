/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:36:20 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/10 14:22:05 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_env_entrie(t_shell *shell, char *pwd_type, char *pwd_path)
{
	char	*pwd_entry;

	if (!pwd_path)
	{
		if (!shell->old_pwd)
			return (NULL);
		pwd_path = shell->old_pwd;
	}
	pwd_entry = ft_strjoin(pwd_type, pwd_path);
	if (!pwd_entry)
		error(shell, MALLOC, FATAL, 1);
	return (pwd_entry);
}

static void	update_wd_env(t_shell *shell)
{
	char		*oldpwd;
	char		*pwd;
	// static int	i = 0;

	if (find_in_array(shell->env, "OLDPWD"))
	{
		oldpwd = create_env_entrie(shell, "OLDPWD=", ft_getenv(shell, "PWD"));
		if (!oldpwd)
			return ;
		remove_from_array(shell->env, "OLDPWD");
		shell->env = add_to_array(shell, shell->env, oldpwd, FREEABLE);
		free(oldpwd);
	}
	if (find_in_array(shell->env, "PWD="))
	{
		pwd = create_env_entrie(shell, "PWD=", shell->pwd);
		if (!pwd)
			return ;
		remove_from_array(shell->env, "PWD");
		shell->env = add_to_array(shell, shell->env, pwd, FREEABLE);
		free(pwd);
	}
}

static void	update_wd(t_shell *shell)
{
	if (shell->old_pwd)
		free(shell->old_pwd);
	if (shell->pwd)
	{
		shell->old_pwd = ft_strdup(shell->pwd);
		if (!shell->old_pwd)
			error(shell, MALLOC, FATAL, 1);
	}
	if (shell->pwd)
		free(shell->pwd);
	shell->pwd = getcwd(NULL, 0);
	if (!shell->pwd)
		error(shell, GETCWD, ERROR, 1);
	update_wd_env(shell);
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
