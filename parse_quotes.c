/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:32:14 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/29 14:32:19 by lkonttin         ###   ########.fr       */
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

int	unclosed_quotes(char *line)
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

void	init_t_parse(t_parse *p)
{
	p->i = 0;
	p->k = 0;
	p->inside_singles = 0;
	p->inside_doubles = 0;
	p->in_quotes = 0;
	p->quote = 0;
}

void	null_terminate(char *str, int k)
{
	while (str[k])
	{
		str[k] = '\0';
		k++;
	}
}

void	remove_quotes(char *str)
{
	t_parse	p;

	init_t_parse(&p);
	while (str[p.i])
	{
		if (str[p.i] == '\'' && !p.inside_doubles)
		{
			p.inside_singles = !p.inside_singles;
			p.i++;
			continue ;
		}
		if (str[p.i] == '\"' && !p.inside_singles)
		{
			p.inside_doubles = !p.inside_doubles;
			p.i++;
			continue ;
		}
		str[p.k] = str[p.i];
		p.i++;
		p.k++;
	}
	null_terminate(str, p.k);
}
