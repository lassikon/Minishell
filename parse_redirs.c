/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:03:52 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/12 12:37:06 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	illegal_arrows(char *line, int i)
{
	if (line[i] == '>')
	{
		if (line[i - 1] == '<')
			return (1);
		if (line[i + 1] == '>' || line[i + 1] == '<')
			return (1);
	}
	if (line[i] == '<')
	{
		if (line[i - 1] == '>')
			return (1);
		if (line[i + 1] == '>' || line[i + 1] == '<')
			return (1);
	}
	return (0);
}

static int	count_redirections(char *line)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = skip_quotes(line, i);
		if (line[i] == '>' || line[i] == '<')
		{
			if (illegal_arrows(line, i + 1))
				return (-1);
			if (line[i + 1] == '>' || line[i + 1] == '<')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}


static void	tidy_format(t_shell *shell, t_cmd *cmd, int i)
{
	char	*str;

	str = cmd->redir[i];
	if (str[1] == ' ')
	{
		if (str[2] != ' ')
			return ;
		else
			remove_spaces(&str[2]);
	}
	else if (str[1] == '<' || str[1] == '>')
	{
		if (str[2] == ' ')
			remove_spaces(&str[2]);
	}
	else
		str = add_one_space(str);
	if (!str)
		error(shell, MALLOC, FATAL, 1);
	cmd->redir[i] = str;
}

static int	get_redirection(t_shell *shell, t_cmd *cmd, int i, int index)
{
	int		len;

	(void)shell;
	len = 0;
	while (cmd->line[i + len] == '>' || cmd->line[i + len] == '<')
		len++;
	while (cmd->line[i + len] == ' ')
		len++;
	while (cmd->line[i + len] && cmd->line[i + len] != ' ')
		len++;
	cmd->redir[index] = ft_substr(cmd->line, i, len );
	if (!cmd->redir[index])
		error(shell, MALLOC, FATAL, 1);
	tidy_format(shell, cmd, index);
	remove_quotes(cmd->redir[index]);
	replace_with_spaces(cmd->line, i, i + len);
	return (i + len);
}

int	extract_redirections(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	redir_index;

	i = 0;
	redir_index = 0;
	cmd->redir_count = count_redirections(cmd->line);
	if (cmd->redir_count == -1)
		return (1);
	if (cmd->redir_count == 0)
		return (0);
	cmd->redir = (char **)malloc(sizeof(char *) * (cmd->redir_count + 1));
	if (!cmd->redir)
		error(shell, MALLOC, FATAL, 1);
	while (cmd->line[i])
	{
		if (cmd->line[i] == '\'' || cmd->line[i] == '\"')
			i = skip_quotes(cmd->line, i);
		if (cmd->line[i] == '>' || cmd->line[i] == '<')
		{
			i = get_redirection(shell, cmd, i, redir_index);
			redir_index++;
		}
		else
			i++;
	}
	cmd->redir[cmd->redir_count] = NULL;
	return (0);
}
