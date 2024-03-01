/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:03:52 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/01 16:13:04 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_redirections(char *line)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (line[i + 1] == '>')
			{
				if (line[i] == '>')
					i++;
				else
					return (-1);
			}
			if (line[i + 1] == '<')
			{
				if (line[i] == '<')
					i++;
				else
					return (-1);
			}
			count++;
		}
		i++;
	}
	return (count);
}

static void	delete_from_line(char *line, int start, int end)
{
	while (start < end)
	{
		line[start] = '\0';
		start++;
	}
}

static int	get_redirection(t_shell *shell, t_cmd *cmd, int i, int index)
{
	int		len;

	(void)shell;
	len = 0;
	while (cmd->line[i] == '>' || cmd->line[i] == '<')
		len++;
	if (cmd->line[i + len] == ' ')
	{
		while (cmd->line[i + len] == ' ')
			len++;
	}
	while (cmd->line[i + len] && cmd->line[i + len] != ' ')
		len++;
	cmd->redir[index] = ft_substr(cmd->line, i, len);
	if (!cmd->redir[index])
		exit(1);
	delete_from_line(cmd->line, i, i + len);
	return (i + len);
}

void	extract_redirections(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	redir_count;
	int	redir_index;

	i = 0;
	redir_index = 0;
	redir_count = count_redirections(cmd->line);
	if (redir_count == -1)
		exit(1);
	cmd->redir = (char **)malloc(sizeof(char *) * (redir_count + 1));
	if (!cmd->redir)
		exit(1);
	while (cmd->line[i])
	{
		if (cmd->line[i] == '>' || cmd->line[i] == '<')
		{
			i = get_redirection(shell, cmd, i, redir_index);
			redir_index++;
		}
		else
			i++;
	}
}
