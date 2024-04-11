/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:46:31 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/11 12:17:34 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_pipes(t_shell *shell, char *line)
{
	int	i;

	i = 0;
	if (starts_with_pipe(line) || ends_in_pipe(line))
		return (error(shell, SYNTAX_PIPE, ERROR, 258));
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = skip_quotes(line, i);
		if (line[i] == '|' && line[i + 1])
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '|')
				return (error(shell, SYNTAX_PIPE, ERROR, 258));
		}
		i++;
	}
	return (0);
}

void	mark_actual_pipes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			i = skip_quotes(s, i);
		if (s[i] == '|')
			s[i] = 31;
		i++;
	}
}

int	illegal_arrows(t_shell *shell, char *line, char arrow, int i)
{
	if (line[i] == '\0')
		return (error(shell, SYNTAX_NL, ERROR, 258));
	else if (line[i] == '<' && arrow == '>')
		return (error(shell, SYNTAX_OUTFILE, ERROR, 258));
	else if (line[i] == '>' && arrow == '<')
		return (error(shell, SYNTAX_INFILE, ERROR, 258));
	else if (line[i] == '<' && line[i + 1] == '>')
		return (error(shell, SYNTAX_OUTFILE, ERROR, 258));
	else if (line[i] == '<' && line[i + 1] == '<')
		return (error(shell, SYNTAX_INFILE, ERROR, 258));
	else if (line[i] == '>' && line[i + 1] == '>')
		return (error(shell, SYNTAX_OUTFILE, ERROR, 258));
	else if (line[i] == '>' && line[i + 1] == '<')
		return (error(shell, SYNTAX_INFILE, ERROR, 258));
	i++;
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (error(shell, SYNTAX_NL, ERROR, 258));
	if (line[i] == '>')
		return (error(shell, SYNTAX_OUTFILE, ERROR, 258));
	if (line[i] == '<')
		return (error(shell, SYNTAX_INFILE, ERROR, 258));
	return (0);
}
