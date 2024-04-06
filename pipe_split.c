/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:47:02 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/06 11:44:24 by lkonttin         ###   ########.fr       */
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
		shell->cmd_tree[k].line = get_substr(shell, s, &i);
		tokenize(shell, &shell->cmd_tree[k]);
		k++;
	}
}
