/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:03:52 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/11 12:19:32 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redirections(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->line[i])
	{
		if (cmd->line[i] == '\'' || cmd->line[i] == '\"')
			i = skip_quotes(cmd->line, i);
		if (cmd->line[i] == '>' || cmd->line[i] == '<')
		{
			if (cmd->line[i + 1] != '\"' && cmd->line[i + 1] != '\'')
			{
				if (illegal_arrows(shell, cmd->line, cmd->line[i], i + 1))
					return (1);
			}
			if (cmd->line[i + 1] == '>' || cmd->line[i + 1] == '<')
				i++;
			cmd->redir_count++;
		}
		i++;
	}
	if (cmd->redir_count == 0)
		return (1);
	return (0);
}

static void	tidy_format(t_shell *shell, t_cmd *cmd, int k)
{
	char	*str;

	str = cmd->redir[k];
	if (str[1] == ' ')
	{
		if (str[2] == ' ')
			remove_spaces(&str[2]);
	}
	else if (str[1] == '<' || str[1] == '>')
	{
		if (str[2] == ' ')
			remove_spaces(&str[2]);
	}
	else
	{
		str = add_one_space(str);
		if (!str)
			error(shell, MALLOC, FATAL, 1);
	}
	cmd->redir[k] = str;
	remove_quotes(cmd->redir[k]);
}

static char	*get_redirection(t_shell *shell, char *line, int *i)
{
	t_parse	p;
	char	*str;

	init_t_parse(&p);
	p.k = *i;
	while (line[*i] == '>' || line[*i] == '<')
		(*i)++;
	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] == '\'' || line[*i] == '\"')
		*i = skip_quotes(line, *i) + 1;
	while (line[*i] && line[*i] != ' ' && line[*i] != '>' && line[*i] != '<')
		(*i)++;
	str = ft_substr(line, p.k, *i - p.k);
	if (!str)
		error(shell, MALLOC, FATAL, 1);
	return (str);
}

void	extract_redirections(t_shell *shell, t_cmd *cmd)
{
	t_parse	p;

	init_t_parse(&p);
	if (check_redirections(shell, cmd))
		return ;
	cmd->redir = (char **)malloc(sizeof(char *) * (cmd->redir_count + 1));
	if (!cmd->redir)
		error(shell, MALLOC, FATAL, 1);
	while (cmd->line[p.i])
	{
		if (cmd->line[p.i] == '\'' || cmd->line[p.i] == '\"')
			p.i = skip_quotes(cmd->line, p.i) + 1;
		else if (cmd->line[p.i] == '>' || cmd->line[p.i] == '<')
		{
			p.j = p.i;
			cmd->redir[p.k] = get_redirection(shell, cmd->line, &p.i);
			tidy_format(shell, cmd, p.k);
			replace_with_spaces(cmd->line, p.j, p.i);
			p.k++;
		}
		else
			p.i++;
	}
	cmd->redir[p.k] = NULL;
}
