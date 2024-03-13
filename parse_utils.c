/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:19:44 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/13 14:23:11 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_one_space(char *str)
{
	char *new;

	if (str[0] == '<')
		new = ft_strjoin("< ", &str[1]);
	else
		new = ft_strjoin("> ", &str[1]);
	if (!new)
		return (NULL);
	free(str);
	return (new);
}

void	remove_spaces(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}

void	replace_with_spaces(char *line, int start, int end)
{
	while (start < end)
	{
		line[start] = ' ';
		start++;
	}
}

int	skip_quotes(char *line, int i)
{
	char	quote;

	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	return (i + 1);
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
			if (inside_singles)
				continue ;
		}
		if (str[i] == '\"' && !inside_singles)
		{
			inside_doubles = !inside_doubles;
			i++;
			if (inside_doubles)
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

/* void	remove_quotes(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == '\'' || str[i] == '\"'))
			i++;
		str[j] = str[i];
		i++;
		j++;
	}
	while (str[j])
	{
		str[j] = '\0';
		j++;
	}
} */
