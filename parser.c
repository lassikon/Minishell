/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:30:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/08 18:01:45 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_commands(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == 31)
			count++;
		i++;
	}
	return (count + 1);
}

static char	*get_substr(t_shell *shell, char *s, int *i)
{
	int		start;
	char	*substr;

	start = *i;
	while (s[*i] && s[*i] != 31)
		(*i)++;
	substr = ft_substr(s, start, *i - start);
	if (!substr)
		error(shell, MALLOC, FATAL, 1);
	if (s[*i])
		(*i)++;
	return (substr);
}

static void	tokenize(t_shell *shell, t_cmd *cmd)
{
	if (unclosed_quotes(cmd->line))
	{
		error(shell, SYNTAX_QUOTES, ERROR, 1);
		return ;
	}
	extract_redirections(shell, cmd);
	if (cmd->redir_count > 0 && shell->status != ERROR)
		heredoc(shell, cmd);
	if (shell->status == ERROR)
		return ;
	if (ft_strchr(cmd->line, '$'))
		expand(shell, &cmd->line);
	if (only_spaces(cmd->line))
		return ;
	extract_command(shell, cmd);
	extract_args(shell, cmd);
}

static void	pipe_split(t_shell *shell, char *s)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	mark_actual_pipes(s);
	shell->cmd_count = count_commands(s);
	init_tree(shell);
	while (s[i] && k < shell->cmd_count && shell->status != ERROR)
	{
		shell->cmd_tree[k].index = k;
		shell->cmd_tree[k].line = get_substr(shell, s, &i);
		tokenize(shell, &shell->cmd_tree[k]);
		k++;
	}
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
	if (unclosed_quotes(shell->line))
	{
		error(shell, SYNTAX_QUOTES, ERROR, 1);
		return ;
	}
	if (invalid_pipes(shell, shell->line))
		return ;
	pipe_split(shell, shell->line);
}
