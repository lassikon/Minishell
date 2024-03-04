/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:30:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/04 17:52:13 by okarejok         ###   ########.fr       */
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

void	m_split(t_shell *shell, int i)
{
	if (check_unclosed_quotes(shell->cmd_tree[i].line))
	{
		printf("Error: Unclosed quotes in cmd[%d]\n", i);
		return ;
	}
	if (extract_redirections(shell, &shell->cmd_tree[i]))
	{
		printf("Error: Redirections in cmd[%d]\n", i);
		return ;
	}
	extract_command(shell, &shell->cmd_tree[i]);
	extract_args(shell, &shell->cmd_tree[i]);
	shell->cmd_tree[i].cmd_index = i;
}

void	parse_line(t_shell *shell)
{
	int	i;

	// printf("checking for pipes\n");
	if (!ft_strchr(shell->line, '|'))
	{
		shell->cmd_count = 1;
		shell->cmd_tree = malloc(sizeof(t_cmd) * 2);
		shell->cmd_tree[0].line = ft_strdup(shell->line);
		shell->cmd_tree[1].line = NULL;
		m_split(shell, 0);
		return ;
	}
	// printf("splitting pipes\n");
	shell->pipe_split = ft_split(shell->line, '|');
	shell->cmd_count = 0;
	while (shell->pipe_split[shell->cmd_count])
		shell->cmd_count++;
	// printf("cmd_count: %d\n", shell->cmd_count);
	// printf("init tree\n");
	init_tree(shell);
	i = 0;
	while (shell->pipe_split[i])
	{
		// printf("parsing cmd %d\n", i);
		shell->cmd_tree[i].line = ft_strdup(shell->pipe_split[i]);
		m_split(shell, i);
		free(shell->pipe_split[i]);
		i++;
	}
	shell->cmd_tree[i].line = NULL;
	free(shell->pipe_split);
}
