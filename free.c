/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:15:57 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/05 17:26:39 by lkonttin         ###   ########.fr       */
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
	while (i < shell->cmd_count)
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

void	free_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		free(shell->pipe[i]);
		i++;
	}
	free(shell->pipe);
	shell->pipe = NULL;
}

void	free_all(t_shell *shell)
{
	if (shell->pipe)
		free_pipes(shell);
	if (shell->pid)
		free(shell->pid);
	if (shell->paths)
		free_array(shell->paths);
	if (shell->cmd_tree)
		free_tree(shell);
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
}
