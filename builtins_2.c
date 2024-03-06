/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:36:20 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/06 17:49:10 by okarejok         ###   ########.fr       */
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
	(void)shell;
	if (ft_strncmp(cmd->args[1], "-n", 2) == 0)
		ft_putstr_fd(cmd->args[2], 1);
	else
		ft_putendl_fd(cmd->args[1], 1);
	exit(1);
}

void	ft_exit(t_shell *shell, t_cmd *cmd)
{
	(void)shell;
	(void)cmd;
	//free_all(shell)
	exit(1);
}
