/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:30:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/01 21:56:49 by lkonttin         ###   ########.fr       */
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

void	m_split(t_shell *shell, t_cmd *cmd)
{
	extract_redirections(shell, cmd);
	// extract_command(shell, cmd);
	// extract_args(shell, cmd);
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
		m_split(shell, &shell->cmd_tree[0]);
		return ;
	}
	// printf("splitting pipes\n");
	shell->pipe_split = ft_split(shell->line, '|');
	while (shell->pipe_split[shell->cmd_count])
		shell->cmd_count++;
	// printf("init tree\n");
	init_tree(shell);
	i = 0;
	while (shell->pipe_split[i])
	{
		shell->cmd_tree[i].line = ft_strdup(shell->pipe_split[i]);
		m_split(shell, &shell->cmd_tree[i]);
		free(shell->pipe_split[i]);
		i++;
	}
	free(shell->pipe_split);
}
