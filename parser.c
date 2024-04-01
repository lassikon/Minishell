/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:30:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/01 14:30:31 by lkonttin         ###   ########.fr       */
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
	extract_redirections(shell, cmd);
	if (cmd->redir_count > 0 && shell->status != ERROR)
		heredoc(shell, cmd);
	if (ft_strchr(cmd->line, '$'))
		cmd->expands = expand(shell, &cmd->line);
	extract_command(shell, cmd);
	extract_args(shell, cmd);
}

void	parse_line(t_shell *shell)
{
	setup_prompt(shell);
	if (shell->status == ERROR)
		return ;
	convert_tabs_to_spaces(shell->line);
	if (only_spaces(shell->line))
	{
		shell->status = ERROR;
		return ;
	}
	if (invalid_pipes(shell, shell->line))
		return ;
	pipe_split(shell, shell->line);
	if (shell->status == ERROR || shell->cmd_count == 0)
		return ;
}
