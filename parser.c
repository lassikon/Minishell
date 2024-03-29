/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:30:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/29 10:36:46 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize(t_shell *shell, t_cmd *cmd)
{
	if (unclosed_quotes(cmd->line))
	{
		error(shell, SYNTAX_QUOTES, ERROR, 1);
		return ;
	}
	convert_tabs_to_spaces(cmd->line);
	extract_redirections(shell, cmd);
	if (ft_strchr(cmd->line, '$'))
		check_expands(shell, &cmd->line);
	if (cmd->redir_count > 0 && shell->status != ERROR)
		heredoc(shell, cmd);
	extract_command(shell, cmd);
	extract_args(shell, cmd);
}

void	parse_line(t_shell *shell)
{
	setup_prompt(shell);
	if (shell->status == ERROR)
		return ;
	if (invalid_pipes(shell, shell->line))
		return ;
	pipe_split(shell, shell->line);
	if (shell->status == ERROR || shell->cmd_count == 0)
		return ;
	if (!shell->cmd_tree[0].cmd[0] && shell->cmd_tree[0].redir_count == 0)
	{
		shell->status = ERROR;
		return ;
	}
}
