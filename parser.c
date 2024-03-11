/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:30:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/11 12:00:48 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
SPLIT IDEA

Extracted parts in the line get replaced with ' '.

1. Extract redirections from the line and store them in the t_cmd struct.
	- Redirection arrows and filenames are stored in an array.
	- File is the first word after the redirection arrow.

2. Extract the command from the line and store it in the t_cmd struct.
	- Command is the first word that is not a filename for a redirection.
	- After this point, whatever is left of the line should be arguments.

3. Extract the arguments from the line and store them in the t_cmd struct.
	- Arguments are split into an array of strings.
*/

char	*join_n_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new);
}

int	check_unclosed_quotes(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (!line[i])
				return (1);
		}
		i++;
	}
	return (0);
}

void	m_split(t_shell *shell, t_cmd *cmd)
{
	check_expands(shell, cmd);
	if (check_unclosed_quotes(cmd->line))
	{
		printf("Error: Unclosed quotes in cmd[%d]\n", cmd->index);
		return ;
	}
	if (extract_redirections(shell, cmd))
	{
		printf("Error: Redirections in cmd[%d]\n", cmd->index);
		return ;
	}
	heredoc(shell, cmd);
	extract_command(shell, cmd);
	extract_args(shell, cmd);
}

void	parse_line(t_shell *shell)
{
	int	i;

	shell->pipe_split = ft_split(shell->line, '|');
	shell->cmd_count = 0;
	while (shell->pipe_split[shell->cmd_count])
		shell->cmd_count++;
	init_tree(shell);
	i = 0;
	while (shell->pipe_split[i])
	{
		shell->cmd_tree[i].index = i;
		shell->cmd_tree[i].line = ft_strdup(shell->pipe_split[i]);
		m_split(shell, &shell->cmd_tree[i]);
		free(shell->pipe_split[i]);
		i++;
	}
	shell->cmd_tree[i].line = NULL;
	free(shell->pipe_split);
}
