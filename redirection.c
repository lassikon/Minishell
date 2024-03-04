/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:30:18 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/04 15:35:34 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipes(t_shell *shell)
{
	if (pipe(shell->pipe) < 0)
	{
		printf("Error pipe\n");
		exit(1);
	}
}

void	close_pipes(t_shell *shell)
{
	close(shell->pipe[1]);
	close(shell->pipe[0]);
}

void	redir_to_pipe(t_shell *shell, int index)
{
	printf("Command count: %d\n", shell->cmd_count);
	printf("Index in pipe: %d\n", index);
	printf("Index + 1 in pipe: %d\n", index + 1);
	if (index + 1 == 1)
	{
		dup2(shell->pipe[1], STDOUT_FILENO);
		close_pipes(shell);
		close(STDIN_FILENO);
	}
	else if (index + 1 < shell->cmd_count)
	{
		dup2(shell->pipe[1], STDOUT_FILENO);
		dup2(shell->pipe[0], STDIN_FILENO);
		close_pipes(shell);
	}
	else if (index + 1 == shell->cmd_count)
	{
		dup2(shell->pipe[0], STDIN_FILENO);
		close_pipes(shell);
	}
}

void	redir_to_file(t_shell *shell)
{
	int i = 0;
	int infile;
	int outfile;
	printf("%s\n", shell->cmd_tree->redir[i]);
	while (shell->cmd_tree->redir[i])
	{
		if (ft_strncmp(&shell->cmd_tree->redir[i][0], "< ", 2) == 0)
		{
			infile = open(&shell->cmd_tree->redir[i][0] + 2, O_RDONLY);
			dup2(infile, STDIN_FILENO);
			close(infile);
		}
		else if (ft_strncmp(&shell->cmd_tree->redir[i][0], "> ", 2) == 0)
		{
			outfile = open(&shell->cmd_tree->redir[i][0] + 2, O_CREAT | O_RDWR | O_TRUNC, 0644);
			dup2(outfile, STDOUT_FILENO);
			close(outfile);
		}
		else if (ft_strncmp(&shell->cmd_tree->redir[i][0], ">>", 2) == 0)
		{
			outfile = open(&shell->cmd_tree->redir[i][0] + 2, O_CREAT | O_APPEND | O_RDWR);
			dup2(outfile, STDOUT_FILENO);
			close(outfile);
		}
		i++;
	}
}