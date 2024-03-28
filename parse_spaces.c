/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:13:42 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/28 11:27:20 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	convert_tabs_to_spaces(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			i = skip_quotes(line, i);
			continue ;
		}
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
}
