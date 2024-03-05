/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:19:16 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/05 10:51:38 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_command(t_cmd *cmd)
{
	cmd->line = NULL;
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->redir_count = 0;
}

void	init_tree(t_shell *shell)
{
	int	i;

	i = 0;
	shell->cmd_tree = malloc(sizeof(t_cmd) * (shell->cmd_count + 1));
	if (!shell->cmd_tree)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	while (i < shell->cmd_count)
	{
		init_command(&shell->cmd_tree[i]);
		i++;
	}
	shell->cmd_tree[i].line = NULL;
}

void	setup_shell(t_shell *shell, char **envp)
{
	shell->pipe_split = NULL;
	shell->line = NULL;
	shell->status = 1;
	shell->env = envp;
	shell->cmd_count = 0;
	shell->line_len = 0;
	paths(shell, envp);
}