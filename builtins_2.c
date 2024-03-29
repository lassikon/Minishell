/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:36:20 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/29 12:02:30 by lkonttin         ###   ########.fr       */
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

void	pwd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	(void)cmd;
	path = ft_getenv(shell, "PWD");
	if (!path)
	{
		path = getcwd(NULL, 0);
	}
	printf("%s\n", path);
	if (path)
		free(path);
}

static void	echo_n(t_cmd *cmd)
{
	int	i;

	i = 2;
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

void	echo(t_shell *shell, t_cmd *cmd)
{
	int	i;

	(void)shell;
	if (!cmd->args[1])
	{
		ft_putchar_fd('\n', 1);
		if (shell->status != ERROR)
			shell->exit_status = 0;
		return ;
	}
	if (ft_strncmp(cmd->args[1], "-n", 2) == 0)
		echo_n(cmd);
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			ft_putstr_fd(cmd->args[i], 1);
			if (cmd->args[i + 1])
				ft_putchar_fd(' ', 1);
			i++;
		}
		ft_putchar_fd('\n', 1);
	}
	if (shell->status != ERROR)
		shell->exit_status = 0;
}

void	env(t_shell *shell, int export)
{
	int	i;
	int	k;

	i = 0;
	printf("executing env\n");
	if (!shell->env)
		return ;
	while (shell->env[i])
	{
		if (export)
		{
			k = 0;
			write(1, "declare -x ", 11);
			while (shell->env[i][k] && shell->env[i][k] != '=')
			{
				write(1, &shell->env[i][k], 1);
				k++;
			}
			printf("=\"%s\"\n", &shell->env[i][k + 1]);
		}
		else
			printf("%s\n", shell->env[i]);
		i++;
	}
}

