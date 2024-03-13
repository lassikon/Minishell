/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:47:02 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/13 12:38:19 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mark_actual_pipes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			i = skip_quotes(s, i);
		if (s[i] == '|')
			s[i] = 31;
		i++;
	}
}

static int	validate_syntax(t_shell *shell, char *s)
{
	int	i;

	i = 0;
	if (check_unclosed_quotes(s))
	{
		error(shell, "Unclosed quotes", ERROR, 1);
		return (1);
	}
	while (s[i])
	{
		if (s[i] == 31 && s[i + 1] == 31)
		{
			error(shell, "syntax error near unexpected token `|'", ERROR, 258);
			return (1);
		}
		i++;
	}
	return (0);
}

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

static int	get_substr(t_shell *shell, char *s, int i, int k)
{
	int	start;

	start = i;
	while (s[i] && s[i] != 31)
		i++;
	shell->cmd_tree[k].line = ft_substr(s, start, i - start);
	if (!shell->cmd_tree[k].line)
		error(shell, MALLOC, FATAL, 1);
	return (i + 1);
}

void	pipe_split(t_shell *shell, char *s)
{
	int	i;
	int	k;

	i = 0;
	k = 0;

	mark_actual_pipes(s);
	if (validate_syntax(shell, s))
		return ;
	shell->cmd_count = count_commands(s);
	init_tree(shell);
	while (s[i] && k < shell->cmd_count)
	{
		shell->cmd_tree[k].index = k;
		i = get_substr(shell, s, i, k);
		if (!shell->cmd_tree[k].line)
			error(shell, MALLOC, ERROR, 1);
		tokenize(shell, &shell->cmd_tree[k]);
		k++;
	}
	shell->cmd_tree[k].line = NULL;
}
/* void	parse_line(t_shell *shell)
{
	int	i;

	if (shell->status == ERROR)
		return ;
	if (ft_strcmp(shell->line, "exit") == 0)
		ft_exit(shell);
	shell->pipe_split = ft_split(shell->line, '|');
	if (!shell->pipe_split)
		error(shell, MALLOC, ERROR, 1);
	shell->cmd_count = 0;
	while (shell->pipe_split[shell->cmd_count])
		shell->cmd_count++;
	init_tree(shell);
	i = 0;
	while (shell->status == RUNNING && shell->pipe_split[i])
	{
		shell->cmd_tree[i].index = i;
		shell->cmd_tree[i].line = ft_strdup(shell->pipe_split[i]);
		if (!shell->cmd_tree[i].line)
			error(shell, MALLOC, ERROR, 1);
		m_split(shell, &shell->cmd_tree[i]);
		free(shell->pipe_split[i]);
		i++;
	}
	shell->cmd_tree[i].line = NULL;
	free(shell->pipe_split);
} */