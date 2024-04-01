/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:36:20 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/01 11:06:25 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_wd(t_shell *shell)
{
	char	*oldpwd_path;
	char	*pwd_path;
	char	*oldpwd_entry;
	char	*pwd_entry;

	pwd_path = getcwd(NULL, 0);
	if (!pwd_path)
		return ;
	oldpwd_path = ft_getenv(shell, "PWD");
	if (!oldpwd_path)
	{
		free(pwd_path);
		return ;
	}
	remove_from_array(shell->env, "OLDPWD");
	remove_from_array(shell->env, "PWD");
	pwd_entry = ft_strjoin("PWD=", pwd_path);
	if (!pwd_entry)
		error(shell, MALLOC, FATAL, 1);
	oldpwd_entry = ft_strjoin("OLDPWD=", oldpwd_path);
	if (!oldpwd_entry)
		error(shell, MALLOC, FATAL, 1);
	shell->env = add_to_array(shell->env, pwd_entry);
	shell->env = add_to_array(shell->env, oldpwd_entry);
	free(oldpwd_path);
	free(pwd_path);
	free(oldpwd_entry);
	free(pwd_entry);
}

static void	cd_error(t_shell *shell, char *path)
{
	char	*error_msg;

	error_msg = ft_strjoin("cd: ", path);
	p_error(shell, error_msg, ERROR, 1);
	free(error_msg);
}

void	cd(t_shell *shell, t_cmd *cmd)
{
	char	*home;
	char	*path;

	if (!cmd->args[1])
		path = ft_getenv(shell, "HOME");
	else if (ft_strncmp(&cmd->args[1][0], "~", 1) == 0)
	{
		home = ft_getenv(shell, "HOME");
		path = ft_strjoin(home, &cmd->args[1][1]);
		free(home);
	}
	else if (ft_strncmp(&cmd->args[1][0], "-", 1) == 0)
		path = ft_getenv(shell, "OLDPWD");
	else
		path = ft_strdup(cmd->args[1]);
	if (!path)
		error(shell, MALLOC, FATAL, 1);
	if (chdir(path) == -1)
		cd_error(shell, path);
	else
		update_wd(shell);
	free(path);
}
