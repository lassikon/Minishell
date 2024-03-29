/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:47:02 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/29 14:32:33 by lkonttin         ###   ########.fr       */
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
	while (s[i] && k < shell->cmd_count && shell->status != ERROR)
	{
		shell->cmd_tree[k].index = k;
		i = get_substr(shell, s, i, k);
		if (!shell->cmd_tree[k].line)
			error(shell, MALLOC, FATAL, 1);
		tokenize(shell, &shell->cmd_tree[k]);
		k++;
	}
	shell->cmd_tree[k].line = NULL;
}
