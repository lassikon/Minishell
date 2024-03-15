/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:30:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/15 16:12:46 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	tokenize(t_shell *shell, t_cmd *cmd)
{
	check_expands(shell, cmd);
	if (check_unclosed_quotes(cmd->line))
	{
		error(shell, "Unclosed quotes", ERROR, 1);
		return ;
	}
	if (extract_redirections(shell, cmd))
	{
		error(shell, "Redirection", ERROR, 1);
		return ;
	}
	heredoc(shell, cmd);
	extract_command(shell, cmd);
	extract_args(shell, cmd);
}

void	parse_line(t_shell *shell)
{
	if (shell->status == ERROR)
		return ;
	pipe_split(shell, shell->line);
}
