/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:30:18 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/03 17:04:44 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_and_close(int file, int fd)
{
	if (file == -1)
		return ;
	dup2(file, fd);
	close(file);
}

void	redir_to_pipe(t_shell *shell, t_cmd *cmd_vars)
{
	if (cmd_vars->index == 0)
	{
		dup2(shell->pipe[cmd_vars->index][1], STDOUT_FILENO);
		close_pipes(shell);
	}
	else if (cmd_vars->index < shell->cmd_count - 1)
	{
		dup2(shell->pipe[cmd_vars->index][1], STDOUT_FILENO);
		dup2(shell->pipe[cmd_vars->index - 1][0], STDIN_FILENO);
		close_pipes(shell);
	}
	else if (cmd_vars->index == shell->cmd_count - 1)
	{
		dup2(shell->pipe[cmd_vars->index - 1][0], STDIN_FILENO);
		close_pipes(shell);
	}
}

void	redir_to_file(t_shell *shell, t_cmd *cmd, t_status mode)
{
	int	i;

	i = 0;
	while (cmd->redir[i] && shell->status != ERROR)
	{
		if (ft_strncmp(&cmd->redir[i][0], "< ", 2) == 0)
		{
			cmd->infile = open(cmd->redir[i] + 2, O_RDONLY);
			dup_and_close(cmd->infile, STDIN_FILENO);
		}
		else if (ft_strncmp(&cmd->redir[i][0], "> ", 2) == 0)
		{
			cmd->outfile = open(cmd->redir[i] + 2, OPEN_OUT, 0644);
			dup_and_close(cmd->outfile, STDOUT_FILENO);
		}
		else if (ft_strncmp(&cmd->redir[i][0], ">>", 2) == 0)
		{
			cmd->outfile = open(cmd->redir[i] + 2, OPEN_APPEND, 0644);
			dup_and_close(cmd->outfile, STDOUT_FILENO);
		}
		if (cmd->infile == -1 || cmd->outfile == -1)
			p_error(shell, cmd->redir[i] + 2, mode, 1);
		i++;
	}
}
