/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:36:20 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/15 16:15:58 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_shell *shell, t_cmd *cmd)
{
	char	*home;
	char	*path;

	if (!cmd->args[1])
	{
		path = ft_strdup(find_home_dir(shell));
		if (!path)
			error(shell, MALLOC, FATAL, 1);
	}
	else if (ft_strncmp(&cmd->args[1][0], "~", 1) == 0)
	{
		home = find_home_dir(shell);
		path = ft_strjoin(home, &cmd->args[1][1]);
		if (path == NULL)
			error(shell, MALLOC, FATAL, 1);
	}
	else
	{
		path = ft_strdup(cmd->args[1]);
		if (!path)
			error(shell, MALLOC, FATAL, 1);
	}
	if (chdir(path) == -1)
		error(shell, CD_FAIL, ERROR, 1);
	free(path);
}

void	pwd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	(void)shell;
	(void)cmd;
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}

void	echo(t_shell *shell, t_cmd *cmd)
{
	int	i;

	(void)shell;
	if (ft_strncmp(cmd->args[1], "-n", 2) == 0)
	{
		i = 2;
		while (cmd->args[i])
		{
			ft_putstr_fd(cmd->args[i], 1);
			if (cmd->args[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			if (!cmd->args[i + 1])
			{
				ft_putendl_fd(cmd->args[i], 1);
				break ;
			}
			ft_putstr_fd(cmd->args[i], 1);
			ft_putstr_fd(" ", 1);
			i++;
		}
	}
}

void	env(t_shell *shell, int export)
{
	int	i;
	int	k;

	i = 0;
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

// add overflow handling, such as "exit 23492342039402324"
// ctrl + d should write exit
// expand $ in heredoc unless LIMITER is inside quotes
// clear OLDPWD when shell is started

void	ft_exit(t_shell *shell, t_cmd *cmd)
{
	int	code;

	ft_putendl_fd("exit", 1);
	if (cmd->arg_count > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		shell->exit_status = 1;
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
	free(shell->env);
	exit(code);
}
