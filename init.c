/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:19:16 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/10 14:19:24 by lkonttin         ###   ########.fr       */
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
	cmd->infile = -2;
	cmd->out = -2;
	cmd->arg_count = 0;
	cmd->index = 0;
}

void	init_tree(t_shell *shell)
{
	int	i;

	i = 0;
	shell->cmd_tree = (t_cmd *)malloc(sizeof(t_cmd) * (shell->cmd_count + 1));
	if (!shell->cmd_tree)
		error(shell, MALLOC, FATAL, 1);
	while (i < shell->cmd_count)
	{
		init_command(&shell->cmd_tree[i]);
		i++;
	}
	shell->cmd_tree[i].line = NULL;
	shell->pid = (int *)malloc(sizeof(int) * shell->cmd_count);
	if (!shell->pid)
		error(shell, MALLOC, FATAL, 1);
	shell->pid_allocated = 1;
	paths(shell, shell->env);
}

void	setup_prompt(t_shell *shell)
{
	shell->pipe = NULL;
	shell->pipes_allocated = 0;
	shell->cmd_count = 0;
	shell->cmd_tree = NULL;
	shell->pid = NULL;
	shell->pid_allocated = 0;
	shell->paths = NULL;
	shell->heredoc_index = 0;
	shell->parent_redir = 0;
}

void	setup_shell(t_shell *shell, char **envp)
{
	shell->line = NULL;
	shell->status = RUNNING;
	shell->cmd_count = 0;
	shell->cmd_tree = NULL;
	shell->pid = NULL;
	shell->pid_allocated = 0;
	shell->pipe = NULL;
	shell->pipes_allocated = 0;
	shell->paths = NULL;
	shell->exit_status = 0;
	shell->cmd_count = 0;
	shell->paths = NULL;
	shell->old_pwd = NULL;
	shell->pwd = NULL;
	shell->env = copy_array(shell, envp);
	shell->pwd = getcwd(NULL, 0);
	if (!shell->pwd)
		ft_putendl_fd(GETCWD, 2);
	if (isatty(STDIN_FILENO))
	{
		shlvl_increment(shell);
		remove_from_array(shell->env, "OLDPWD");
		shell->env = add_to_array(shell, shell->env, "OLDPWD", 0);
	}
}
