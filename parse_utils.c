/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:19:44 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/22 12:34:44 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_one_space(char *str)
{
	char	*new;

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

int	ends_in_pipe(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i > 0 && line[i] == ' ')
		i--;
	if (line[i] == '|')
		return (1);
	return (0);
}

int	double_pipes(t_shell *shell, char *line)
{
	int	i;

	i = 0;
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
			{
				error(shell, SYNTAX_PIPE, ERROR, 258);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
