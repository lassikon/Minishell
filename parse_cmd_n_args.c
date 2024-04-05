/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_n_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:04:07 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/05 18:12:04 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_command(t_shell *shell, t_cmd *cmd)
{
	int		start;
	int		end;

	if (shell->status == ERROR)
		return ;
	start = 0;
	while (cmd->line[start] && cmd->line[start] == ' ')
		start++;
	end = start;
	while (cmd->line[end] && cmd->line[end] != ' ')
	{
		if (cmd->line[end] == '\'' || cmd->line[end] == '\"')
			end = skip_quotes(cmd->line, end);
		end++;
	}
	cmd->cmd = ft_substr(cmd->line, start, end - start);
	if (!cmd->cmd)
		error(shell, MALLOC, FATAL, 1);
	remove_quotes(cmd->cmd);
	replace_with_spaces(cmd->line, start, end);
}

static int	count_args(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			count++;
			while (line[i] && line[i] != ' ')
			{
				if (line[i] == '\'' || line[i] == '\"')
					i = skip_quotes(line, i);
				i++;
			}
		}
		else
			i++;
	}
	return (count);
}

char	*fetch_substr(t_shell *shell, char *line, int start, int len)
{
	char	*substr;

	if (len == 0)
		return (NULL);
	substr = ft_substr(line, start, len);
	if (!substr)
		error(shell, MALLOC, FATAL, 1);
	return (substr);
}

void	fetch_args(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		start;
	int		k;

	i = 0;
	k = 1;
	while (cmd->line[i])
	{
		while (cmd->line[i] && cmd->line[i] == ' ')
			i++;
		start = i;
		while (cmd->line[i] && cmd->line[i] != ' ')
		{
			if (cmd->line[i] == '\'' || cmd->line[i] == '\"')
				i = skip_quotes(cmd->line, i);
			i++;
		}
		cmd->args[k] = fetch_substr(shell, cmd->line, start, i - start);
		if (!cmd->args[k])
			break ;
		remove_quotes(cmd->args[k]);
		k++;
	}
}

void	extract_args(t_shell *shell, t_cmd *cmd)
{
	if (shell->status == ERROR)
		return ;
	cmd->arg_count = count_args(cmd->line) + 1;
	cmd->args = malloc(sizeof(char *) * (cmd->arg_count + 1));
	if (!cmd->args)
		error(shell, MALLOC, FATAL, 1);
	cmd->args[0] = ft_strdup(cmd->cmd);
	if (!cmd->args[0])
		error(shell, MALLOC, FATAL, 1);
	if (cmd->arg_count > 1)
		fetch_args(shell, cmd);
	cmd->args[cmd->arg_count] = NULL;
}
