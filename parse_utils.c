/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:19:44 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/06 12:07:50 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	starts_with_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (1);
	return (0);
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

char	*dup_empty_str(t_shell *shell)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
		error(shell, MALLOC, FATAL, 1);
	return (str);
}

char	*join_n_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new);
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
