/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:19:16 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/04 12:31:18 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_read_history(t_shell *shell)
{
	char	*line;

	line = get_next_line(shell->history_fd);
	while (line)
	{
		line[ft_strlen(line) - 1] = '\0';
		add_history(line);
		free(line);
		line = get_next_line(shell->history_fd);
	}
}

static void	init_command(t_cmd *cmd)
{
	cmd->line = NULL;
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->redir_count = 0;
	cmd->infile = -2;
	cmd->out = -2;
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
	paths(shell, shell->env);
}

void	setup_prompt(t_shell *shell)
{
	shell->pipe = NULL;
	shell->cmd_count = 0;
	shell->cmd_tree = NULL;
	shell->pid = NULL;
	shell->paths = NULL;
	shell->heredoc_index = 0;
	shell->expand_count = 0;
	shell->parent_redir = 0;
}

void	setup_shell(t_shell *shell, char **envp)
{
	shell->line = NULL;
	shell->status = RUNNING;
	shell->cmd_count = 0;
	shell->cmd_tree = NULL;
	shell->pid = NULL;
	shell->pipe = NULL;
	shell->paths = NULL;
	shell->line_len = 0;
	shell->exit_status = 0;
	shell->history_fd = open("history", O_CREAT | O_APPEND | O_RDWR, 0644);
	ft_read_history(shell);
	shell->env = malloc(sizeof(char *) * (array_len(envp) + 1));
	if (!shell->env)
		error(shell, MALLOC, FATAL, 1);
	if (copy_array(envp, shell->env) == -1)
		error(shell, MALLOC, FATAL, 1);
	if (isatty(STDIN_FILENO))
	{
		shlvl_increment(shell);
		remove_from_array(shell->env, "OLDPWD");
	}
}
