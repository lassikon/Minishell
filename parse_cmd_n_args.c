/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_n_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:04:07 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/01 11:37:56 by lkonttin         ###   ########.fr       */
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
		{
			end = skip_quotes(cmd->line, end);
			continue ;
		}
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
		if (line[i] == '\'' || line[i] == '\"')
		{
			count++;
			i = skip_quotes(line, i);
			continue ;
		}
		if (line[i] != ' ')
		{
			count++;
			while (line[i] && line[i] != ' ')
				i++;
		}
		else
			i++;
	}
	return (count);
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
				i = skip_quotes(cmd->line, i) - 1;
			i++;
		}
		cmd->args[k] = ft_substr(cmd->line, start, i - start);
		if (!cmd->args[k])
			error(shell, MALLOC, FATAL, 1);
		remove_quotes(cmd->args[k]);
		k++;
	}
}

void	extract_args(t_shell *shell, t_cmd *cmd)
{
	int		count;

	if (shell->status == ERROR)
		return ;
	count = count_args(cmd->line);
	cmd->arg_count = count + 1;
	cmd->args = malloc(sizeof(char *) * (count + 2));
	if (!cmd->args)
		error(shell, MALLOC, FATAL, 1);
	cmd->args[0] = ft_strdup(cmd->cmd);
	if (!cmd->args[0])
		error(shell, MALLOC, FATAL, 1);
	if (cmd->arg_count > 1)
		fetch_args(shell, cmd);
	cmd->args[cmd->arg_count] = NULL;
}
