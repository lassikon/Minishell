/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:52:14 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/12 14:22:36 by lkonttin         ###   ########.fr       */
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
		if (shell->pipe[i][0] == -1 || shell->pipe[i][1] == -1)
			p_error(shell, "pipe", FATAL, 1);
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