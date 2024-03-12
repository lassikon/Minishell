/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:15:57 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/12 15:01:20 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	free_tree(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->cmd_tree)
		return ;
	while (shell->cmd_tree[i].line)
	{
		if (shell->cmd_tree[i].line)
		{
			free(shell->cmd_tree[i].line);
			shell->cmd_tree[i].line = NULL;
		}
		if (shell->cmd_tree[i].cmd)
		{
			free(shell->cmd_tree[i].cmd);
			shell->cmd_tree[i].cmd = NULL;
		}
		if (shell->cmd_tree[i].args)
			free_array(shell->cmd_tree[i].args);
		if (shell->cmd_tree[i].redir)
			free_array(shell->cmd_tree[i].redir);
		i++;
	}
	free(shell->cmd_tree);
	shell->cmd_tree = NULL;
}

void	free_all(t_shell *shell)
{
	if (shell->paths)
		free_array(shell->paths);
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (shell->pipe_split)
		free_array(shell->pipe_split);
	free_tree(shell);
}
