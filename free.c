/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:15:57 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/06 19:21:42 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char ***array)
{
	int	i;

	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
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
			free_array(&shell->cmd_tree[i].args);
		if (shell->cmd_tree[i].redir)
			free_array(&shell->cmd_tree[i].redir);
		i++;
	}
	free(shell->cmd_tree);
	shell->cmd_tree = NULL;
}

void	free_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->pipes_allocated)
	{
		free(shell->pipe[i]);
		// shell->pipe[i] = NULL;
		i++;
	}
	free(shell->pipe);
	// shell->pipe = NULL;
	shell->pipes_allocated = 0;
}

void	free_all(t_shell *shell)
{
	if (shell->pipes_allocated > 0)
		free_pipes(shell);
	if (shell->pid_allocated)
	{
		free(shell->pid);
		shell->pid_allocated = 0;
	}
	if (shell->paths)
		free_array(&shell->paths);
	if (shell->cmd_tree)
		free_tree(shell);
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
}
