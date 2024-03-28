/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:30:18 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/28 12:08:20 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_and_close(int file, int fd)
{
	dup2(file, fd);
	close(file);
}

static void	open_file(t_shell *shell, char *redir, int *file, char *mode)
{
	if (ft_strncmp(mode, "> ", 2) == 0)
	{
		*file = open(redir + 2, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (*file == -1)
			p_error(shell, redir + 2, FATAL, 1);
	}
	else if (ft_strncmp(mode, "< ", 2) == 0)
	{
		*file = open(redir + 2, O_RDONLY);
		if (*file == -1)
			p_error(shell, redir + 2, FATAL, 1);
	}
	else if (ft_strncmp(mode, ">>", 2) == 0)
	{
		*file = open(redir + 2, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (*file == -1)
			p_error(shell, redir + 2, FATAL, 1);
	}
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

void	redir_to_file(t_shell *shell, t_cmd *cmd_vars)
{
	int	i;

	i = 0;
	(void)shell;
	while (cmd_vars->redir[i])
	{
		if (ft_strncmp(&cmd_vars->redir[i][0], "< ", 2) == 0)
		{
			open_file(shell, cmd_vars->redir[i], &cmd_vars->infile, "< ");
			dup_and_close(cmd_vars->infile, STDIN_FILENO);
		}
		else if (ft_strncmp(&cmd_vars->redir[i][0], "> ", 2) == 0)
		{
			open_file(shell, cmd_vars->redir[i], &cmd_vars->outfile, "> ");
			dup_and_close(cmd_vars->outfile, STDOUT_FILENO);
		}
		else if (ft_strncmp(&cmd_vars->redir[i][0], ">>", 2) == 0)
		{
			open_file(shell, cmd_vars->redir[i], &cmd_vars->outfile, ">>");
			dup_and_close(cmd_vars->outfile, STDOUT_FILENO);
		}
		i++;
	}
}
