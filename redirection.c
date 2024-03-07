/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:30:18 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/07 14:56:06 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		pipe(shell->pipe[i]);
		i++;
	}
}

void	close_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		close(shell->pipe[i][0]);
		close(shell->pipe[i][1]);
		i++;
	}
}

void	redir_to_pipe(t_shell *shell, int index)
{
	if (index + 1 == 1)
	{
		dup2(shell->pipe[index][1], STDOUT_FILENO);
		close_pipes(shell);
	}
	else if (index + 1 < shell->cmd_count)
	{
		dup2(shell->pipe[index][1], STDOUT_FILENO);
		dup2(shell->pipe[index - 1][0], STDIN_FILENO);
		close_pipes(shell);
	}
	else if (index + 1 == shell->cmd_count)
	{
		dup2(shell->pipe[index - 1][0], STDIN_FILENO);
		close_pipes(shell);
	}
}

void	redir_to_file(t_shell *shell, int index)
{
	int i;
	
	i = 0;
	while (shell->cmd_tree[index].redir[i])
	{
		if (ft_strncmp(&shell->cmd_tree[index].redir[i][0], "< ", 2) == 0)
		{
			shell->cmd_tree[index].infile = open(&shell->cmd_tree[index].redir[i][0] + 2, O_RDONLY);
			dup2(shell->cmd_tree[index].infile , STDIN_FILENO);
			close(shell->cmd_tree[index].infile);
		}
		else if (ft_strncmp(&shell->cmd_tree[index].redir[i][0], "> ", 2) == 0)
		{
			shell->cmd_tree[index].outfile = open(&shell->cmd_tree[index].redir[i][0] + 2, O_CREAT | O_RDWR | O_TRUNC, 0644);
			dup2(shell->cmd_tree[index].outfile, STDOUT_FILENO);
			close(shell->cmd_tree[index].outfile);
		}
		else if (ft_strncmp(&shell->cmd_tree[index].redir[i][0], ">>", 2) == 0)
		{
			shell->cmd_tree[index].outfile = open(&shell->cmd_tree[index].redir[i][0] + 2, O_CREAT | O_APPEND | O_RDWR, 0644);
			dup2(shell->cmd_tree[index].outfile, STDOUT_FILENO);
			close(shell->cmd_tree[index].outfile);
		}
		i++;
	}
}
