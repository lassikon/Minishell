/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:32:14 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/22 12:33:36 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quotes(char *line, int i)
{
	char	quote;

	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	return (i + 1);
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

void	remove_quotes(char *str)
{
	int		i;
	int		k;
	int		inside_singles;
	int		inside_doubles;

	i = 0;
	k = 0;
	inside_singles = 0;
	inside_doubles = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !inside_doubles)
		{
			inside_singles = !inside_singles;
			i++;
			if (inside_singles || str[i] == '\'')
				continue ;
		}
		if (str[i] == '\"' && !inside_singles)
		{
			inside_doubles = !inside_doubles;
			i++;
			if (inside_doubles || str[i] == '\"')
				continue ;
		}
		str[k] = str[i];
		i++;
		k++;
	}
	while (str[k])
	{
		str[k] = '\0';
		k++;
	}
}