/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:52:14 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/06 19:15:19 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	allocate_pipes(shell);
	while (i < shell->cmd_count)
	{
		pipe(shell->pipe[i]);
		if (shell->pipe[i][0] == -1 || shell->pipe[i][1] == -1)
			p_error(shell, PIPE, FATAL, 1);
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

void	allocate_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	shell->pipe = (int **)malloc(shell->cmd_count * sizeof(int *));
	if (shell->pipe == NULL)
		error(shell, MALLOC, FATAL, 1);
	while (i < shell->cmd_count)
	{
		shell->pipe[i] = (int *)malloc(2 * sizeof(int));
		if (!shell->pipe[i])
			error(shell, MALLOC, FATAL, 1);
		shell->pipes_allocated++;
		i++;
	}
}
