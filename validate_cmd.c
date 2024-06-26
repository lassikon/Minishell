/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:40:34 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/10 11:14:46 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	absolute_path_to_directory(char *cmd)
{
	struct stat	buf;

	if (stat(cmd, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			return (1);
	}
	return (0);
}

static int	check_access(t_shell *shell, t_cmd *cmd, char *path, char **c)
{
	if (access(path, 0) == 0)
	{
		if (access(path, X_OK) == -1)
		{
			free(*c);
			free(path);
			p_error(shell, path, FATAL, 126);
		}
		free(cmd->cmd);
		cmd->cmd = path;
		free(*c);
		*c = NULL;
		return (1);
	}
	return (0);
}

static void	check_cmd_path(t_shell *shell, t_cmd *cmd_vars)
{
	int		i;
	char	*cmd_path;
	char	*cmd_one;

	i = -1;
	cmd_one = ft_strjoin("/", cmd_vars->cmd);
	if (cmd_one == NULL)
		error(shell, MALLOC, FATAL, 1);
	while (shell->paths[++i])
	{
		cmd_path = ft_strjoin(shell->paths[i], cmd_one);
		if (!cmd_path)
			error(shell, MALLOC, FATAL, 1);
		if (absolute_path_to_directory(cmd_path))
		{
			free(cmd_path);
			continue ;
		}
		if (check_access(shell, cmd_vars, cmd_path, &cmd_one))
			return ;
		free(cmd_path);
	}
	free(cmd_one);
	child_error(shell, ft_strjoin(cmd_vars->cmd, NO_CMD), FATAL, 127);
}

void	validate_command(t_shell *shell, t_cmd *cmd_vars)
{
	if (cmd_vars->cmd[0] == '\0')
		return ;
	if (ft_strchr(cmd_vars->cmd, '/'))
	{
		if (access(cmd_vars->cmd, F_OK) == -1)
			p_error(shell, cmd_vars->cmd, FATAL, 127);
		else if (access(cmd_vars->cmd, X_OK) == -1)
			p_error(shell, cmd_vars->cmd, FATAL, 126);
		if (absolute_path_to_directory(cmd_vars->cmd))
			child_error(shell, ft_strjoin(cmd_vars->cmd, IS_DIR), FATAL, 126);
	}
	else
	{
		if (shell->paths != NULL)
			check_cmd_path(shell, cmd_vars);
	}
	return ;
}
