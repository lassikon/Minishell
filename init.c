/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:19:16 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/12 16:33:58 by lkonttin         ###   ########.fr       */
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
}

void	init_tree(t_shell *shell)
{
	int	i;

	i = 0;
	shell->cmd_tree = malloc(sizeof(t_cmd) * (shell->cmd_count + 1));
	if (!shell->cmd_tree)
		error(shell, MALLOC, FATAL, 1);
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
	shell->status = RUNNING;
	shell->cmd_count = 0;
	shell->line_len = 0;
	shell->exit_status = 0;
	shell->history_fd = open("history", O_CREAT | O_APPEND | O_RDWR, 0644);
	ft_read_history(shell);
	paths(shell, envp);
	shell->env = malloc(sizeof(char *) * (array_len(envp) + 1));
	if (!shell->env)
		error(shell, MALLOC, FATAL, 1);
	if (copy_array(envp, shell->env) == -1)
		error(shell, MALLOC, FATAL, 1);
}
