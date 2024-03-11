/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:36:20 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/11 11:57:41 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_shell *shell, t_cmd *cmd)
{
	char	*home;
	char	*path;

	home = NULL;
	path = NULL;
	if (!cmd->args[1])
		return ;
	if (ft_strncmp(&cmd->args[1][0], "~", 1) == 0)
	{
		home = find_home_dir(shell);
		path = ft_strjoin(home, &cmd->args[1][1]);
		chdir(path);
		free(path);
	}
	else
	{
		path = cmd->args[1];
		chdir(path);
	}
}

void	pwd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	(void)shell;
	(void)cmd;
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	exit(1);
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
	exit(1);
}

void	env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	exit(0);
}

void	ft_exit(t_shell *shell, t_cmd *cmd)
{
	(void)shell;
	(void)cmd;
	//free_all(shell)
	exit(1);
}
