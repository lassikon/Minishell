/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:36:20 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/28 14:56:13 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_wd(t_shell *shell)
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
	{
		ft_putstr_fd("minishell: cd: ", 2);
		p_error(shell, path, ERROR, 1);
	}
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

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_exit(t_shell *shell, t_cmd *cmd)
{
	int	code;

	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	if (cmd->arg_count > 2)
	{
		error(shell, "minishell: exit: too many arguments", ERROR, 1);
		return ;
	}
	if (cmd->arg_count == 2)
	{
		if (is_numeric(cmd->args[1]))
			code = 255;
		else
			code = ft_atoi(cmd->args[1]);
	}
	else
		code = WEXITSTATUS(shell->exit_status);
	free_all(shell);
	free_array(shell->env);
	close(shell->history_fd);
	toggle_signal(DEFAULT);
	exit(code);
}
