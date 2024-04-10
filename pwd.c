/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:05:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/10 15:08:21 by lkonttin         ###   ########.fr       */
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

void	update_wd(t_shell *shell)
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

void	pwd(t_shell *shell, t_cmd *cmd)
{
	(void)cmd;
	ft_putendl_fd(shell->pwd, 1);
}
