/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_n_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:04:07 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/02 15:52:11 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_command(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		j;

	(void)shell;
	i = 0;
	while (cmd->line[i] && cmd->line[i] == ' ')
		i++;
	j = i;
	while (cmd->line[j] && cmd->line[j] != ' ')
		j++;
	cmd->cmd = ft_substr(cmd->line, i, j - i);
	delete_from_line(cmd->line, i, j);
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
				i++;
		}
		else
			i++;
	}
	return (count);
}

void	extract_args(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		j;
	int		k;
	int		count;

	(void)shell;
	i = 0;
	k = 0;
	count = count_args(cmd->line);
	cmd->args = malloc(sizeof(char *) * (count + 1));
	while (cmd->line[i])
	{
		while (cmd->line[i] && cmd->line[i] == ' ')
			i++;
		j = i;
		while (cmd->line[j] && cmd->line[j] != ' ')
			j++;
		cmd->args[k] = ft_substr(cmd->line, i, j - i);
		i = j;
		k++;
	}
	cmd->args[count] = NULL;
}