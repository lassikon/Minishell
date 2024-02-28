/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:30:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/02/28 16:18:18 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize(t_shell *shell, char *line, int i)
{
	shell->cmd_tree[i] = ft_split(line, ' ');
}

void	parse_line(t_shell *shell)
{
	int i;

	i = 0;
	shell->pipe_split = ft_split(shell->line, '|');
	while (shell->pipe_split[i])
	{
		tokenize(shell, shell->pipe_split[i], i);
		free(shell->pipe_split[i]);
		i++;
	}
	free(shell->pipe_split);
}
