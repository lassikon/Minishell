/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:30:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/02/29 12:16:43 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_split_points(t_shell *shell, char *line)
{
	int	i;

	i = 0;
	shell->line_len = ft_strlen(line);
	while(i < shell->line_len)
	{
		if (line[i] == ' ')
		{
			while (line[i] == ' ' && line[i] != '\0')
			{
				line[i] = '\0';
				i++;
			}
			shell->branch_size++;
		}
		// skip over what's inside quotes
		else if (line[i] == '\"')
		{
			i++;
			while (line[i] != '\"')
				i++;
			i++;
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
			i++;
		}
		else
			i++;
	}
}

void	remove_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			i++;
		str[j] = str[i];
		i++;
		j++;
	}
	while(j < i)
	{
		str[j] = '\0';
		j++;
	}
}

void	split_line(t_shell *shell, char *line, int index)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (i < shell->line_len)
	{
		if (line[i] != '\0')
		{
			shell->cmd_tree[index][k] = ft_strdup(&line[i]);
			remove_quotes(shell->cmd_tree[index][k]);
			while (line[i] != '\0')
				i++;
			k++;
		}
		else
			i++;
	}
	shell->cmd_tree[index][k] = NULL;
}
/*
M_SPLIT IDEA
Iterate through string and replace split points with '\0', then split into array.
Split points are spaces/tabs etc. UNLESS the space is inside closed quotes.
Remove quotes from the strings after splitting.
*/
void	m_split(t_shell *shell, char *line, int i)
{
	add_split_points(shell, line);
	shell->cmd_tree[i] = malloc(sizeof(char *) * (shell->branch_size + 1));
	split_line(shell, line, i);
}

void	allocate_tree(t_shell *shell)
{
	int	i;

	i = 0;
	shell->cmd_tree = malloc(sizeof(char **) * (shell->branch_size + 1));
	while (i < shell->branch_size)
	{
		shell->cmd_tree[i] = NULL;
		i++;
	}
	shell->cmd_tree[i] = NULL;
}

void	parse_line(t_shell *shell)
{
	int	i;

	i = 0;
	shell->pipe_split = ft_split(shell->line, '|');
	allocate_tree(shell);
	while (shell->pipe_split[i])
	{
		m_split(shell, shell->pipe_split[i], i);
		free(shell->pipe_split[i]);
		i++;
	}
	free(shell->pipe_split);
}
