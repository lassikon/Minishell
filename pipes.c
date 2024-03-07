/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:52:14 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/07 14:52:26 by okarejok         ###   ########.fr       */
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